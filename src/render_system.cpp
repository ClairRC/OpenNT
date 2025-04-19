#include "system/render_system.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "components.h"
#include "resources.h"
#include "system/lighting_system.h"

//This whole system is a god damn mess and I need to fix it desparately
//I do not think you understand the mental breakdown that the organization of this
//garbage is giving me.
namespace Systems {
	//Define managers
	//For now these are being stored as static values because they are all pointing to the same managers, 
	//And there is 1 render system. I would like to change both of these facts for better flexibility.
	ResourceManager::ComponentManager* RenderSystem::componentManager = ResourceManager::ComponentManager::getComponentManager();
	ResourceManager::VAOManager* RenderSystem::vaoManager = ResourceManager::VAOManager::getVAOManager();
	Systems::CameraSystem* RenderSystem::cameraSystem = Systems::CameraSystem::getCameraSystem();
	ResourceManager::TextureManager* RenderSystem::textureManager = ResourceManager::TextureManager::getTextureManager();

	void RenderSystem::renderEntities() {
		//Get list of entities
		//TODO: This has to be changed. It is too tightly coupled
		ResourceManager::EntityManager* entityManager = ResourceManager::EntityManager::getEntityManager();
		std::map<std::string, unsigned int>& entityList = entityManager->getEntityList();

		//Get view and projection matrices (once per frame)
		Math::Matrix4 viewMatrix = cameraSystem->getCameraViewMatrix();
		Math::Matrix4 projMatrix = Math::Matrix4::getProjectionMatrix();

		//Get VAO 
		//TODO: For now I'm doing this once, but when I add more vertex data options, I'll have to do it per entity
		unsigned int VAO = vaoManager->getVAO();

		//Loops through entities
		//TODO: I'm going to have to structure this whole thing different so I am not depending on entity manager so much
		for (auto iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
			unsigned int entityID = iterator->second; //Entity we are checking

			//Render if the entity has a position
			if (componentManager->entityHasComponent<Resources::PositionComponent>(entityID)) {
				//Get transformations
				transformations trans = getTransformations(entityID);

				//Get model matrix
				Math::Matrix4 modelMatrix = Math::Matrix4::getModelMatrix(trans.position, trans.rotation, trans.scales);

				//Get Shader
				unsigned int shader = Resources::Shader::loadShader("basic");
				glUseProgram(shader);

				//Gets lighting values to send to shaders
				const Math::Vec3& lighting = LightingSystem::getFrameLightColor();
				const Math::Vec3& position = LightingSystem::getFrameLightPosition();

				unsigned int lightColorLoc = glGetUniformLocation(shader, "lightColor");
				unsigned int lightPosLoc = glGetUniformLocation(shader, "lightPos");

				float lightingVals[] = { lighting.x(), lighting.y(), lighting.z() };
				float lightingPos[] = { position.x(), position.y(), position.z() };

				glUniform3fv(lightColorLoc, 1, lightingVals);
				glUniform3fv(lightPosLoc, 1, lightingPos);

				//Pass in MVP matrices to shaders
				passMVPMatrices(shader, modelMatrix, viewMatrix, projMatrix);

				//Get and bind texture
				//TODO: Allowing multiple texture for an entity is important if I add normal maps
				if (componentManager->entityHasComponent<Resources::TextureComponent>(entityID)) {
					//Gets the texture component
					Resources::TextureComponent texComp = componentManager->getComponent<Resources::TextureComponent>(entityID);

					//Gets the texture ID
					unsigned int textureID = textureManager->getTexture(texComp);

					//Passes the scaling factor and any other texture info to the shaders.
					//Sending the scaling lets the shader basically make a texture repeat if it doesn't fit the quad
					//which is not something that should happen for every object in the world, but I don't have the time
					//to refactor the entire render system and the texture manager and probably more, so I'm going with
					//"simple and works for now"
					unsigned int texScale = glGetUniformLocation(shader, "texScale");
					float scales[] = { trans.scales.x(), trans.scales.y() }; //Scales to send in
					glUniform2fv(texScale, 1, scales);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, textureID);
				}

				//Draw
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}

			//Unbind Things
			//Better grouping should come later so I don't have to bind new things many times per frame.
			glBindVertexArray(0);
			glUseProgram(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	RenderSystem::transformations RenderSystem::getTransformations(const unsigned int entity) {
		//Gets transformations
		Math::Vec3 position = componentManager->getComponent<Resources::PositionComponent>(entity).position;
		Math::Vec3 rotation;
		Math::Vec3 scale(1, 1, 1);

		//Gets rotation Vector if it has it
		if (componentManager->entityHasComponent<Resources::RotationComponent>(entity))
			rotation = (componentManager->getComponent<Resources::RotationComponent>(entity).eRotation);

		//Gets scale vector if it has it
		if (componentManager->entityHasComponent<Resources::ScaleComponent>(entity))
			scale = (componentManager->getComponent<Resources::ScaleComponent>(entity).scales);

		transformations trans;
		trans.position = position;
		trans.rotation = rotation;
		trans.scales = scale;

		return trans;
	}

	void RenderSystem::passMVPMatrices(unsigned int shader, Math::Matrix4& model, Math::Matrix4& view, Math::Matrix4& projection) {
		//Pass in MVP uniforms
		unsigned int mLoc = glGetUniformLocation(shader, "model");
		unsigned int vLoc = glGetUniformLocation(shader, "view");
		unsigned int pLoc = glGetUniformLocation(shader, "projection");

		glUniformMatrix4fv(mLoc, 1, GL_FALSE, model.getDataPointer());
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, view.getDataPointer());
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, projection.getDataPointer());
	}

}