#include "system/lighting_system.h"

#include <glad/glad.h>

#include "resource_manager.h"
#include "components.h"
#include "resources.h"

namespace Systems {
	//Initialize static value
	Math::Vec3 LightingSystem::frameLightColor = Math::Vec3();
	Math::Vec3 LightingSystem::frameLightPosition = Math::Vec3();

	void LightingSystem::calculateLighting() {
		//Get list of entities
		//TODO: This has to be changed. It is too tightly coupled
		ResourceManager::EntityManager* entityManager = ResourceManager::EntityManager::getEntityManager();
		std::map<std::string, unsigned int>& entityList = entityManager->getEntityList();

		//Get component manager
		ResourceManager::ComponentManager* componentManager = ResourceManager::ComponentManager::getComponentManager();

		//Set the frame lighting values to a dummy value so that somethin can always be sent to the shaders
		Math::Vec3 lightColor(0, 0, 0);
		Math::Vec3 lightPosition(0, 0, 0);
		
		for (auto iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
			unsigned int entityID = iterator->second; //Entity we are checking

			//If it has the lighting component...
			if (componentManager->entityHasComponent<Resources::LightSourceComponent>(entityID)) {
				//Okay so right now I'm going to hardcode this to send the information to
				//my shader, since its the only shader I have, but once again, this will need to be changed.
				//I'm not really yet sure how I'll organize this or modularize it, but for now, this is 
				//going to be my solution. Again, due to time constraints

				//Get components
				Resources::LightSourceComponent& lightComp = componentManager->getComponent<Resources::LightSourceComponent>(entityID);

				lightColor.setX(lightComp.lightColor.x());
				lightColor.setY(lightComp.lightColor.y());
				lightColor.setZ(lightComp.lightColor.z());

				lightPosition.setX(lightComp.lightPos.x());
				lightPosition.setY(lightComp.lightPos.y());
				lightPosition.setZ(lightComp.lightPos.z());
			}
		}

		frameLightColor = lightColor;
		frameLightPosition = lightPosition;
	}

	Math::Vec3& LightingSystem::getFrameLightColor() {
		return frameLightColor;
	}

	Math::Vec3& LightingSystem::getFrameLightPosition() {
		return frameLightPosition;
	}
}