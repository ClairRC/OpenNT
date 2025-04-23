#include "system/movement_system.h"

#include "components.h"
#include "resource_manager.h"

/*
* LITERAL GARBAGE!! USELESS!!!!!!!!!!!!!
* This is very much just here to say that I have inputs so people dont make fun of me
* when i have to show a prototype... Kinda necessary for a game engine, but this is
* very much NOT a good class to go off of if you're looking for "software engineering principles"
*/

namespace Systems {
	void MovementSystem::processMovement(GLFWwindow* window) {
		//Get list of entities
		//TODO: This has to be changed. It is too tightly coupled
		ResourceManager::EntityManager* entityManager = ResourceManager::EntityManager::getEntityManager();
		std::map<std::string, unsigned int>& entityList = entityManager->getEntityList();

		//Get component manager
		ResourceManager::ComponentManager* componentManager = ResourceManager::ComponentManager::getComponentManager();

		for (auto iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
			unsigned int entityID = iterator->second; //Entity we are checking

			if (componentManager->entityHasComponent<Resources::MovementComponent>(entityID)
				&& componentManager->entityHasComponent<Resources::PositionComponent>(entityID)) {

				//Get components
				Resources::MovementComponent& moveComp = componentManager->getComponent<Resources::MovementComponent>(entityID);
				Resources::PositionComponent& posComp = componentManager->getComponent<Resources::PositionComponent>(entityID);

				//Get information
				float movementSpeed = moveComp.movementSpeed;
				
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
					posComp.position.setZ(posComp.position.z() - movementSpeed);
				}

				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					posComp.position.setZ(posComp.position.z() + movementSpeed);

				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					posComp.position.setX(posComp.position.x() - movementSpeed);

				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					posComp.position.setX(posComp.position.x() + movementSpeed);
			}
		}
	}
}