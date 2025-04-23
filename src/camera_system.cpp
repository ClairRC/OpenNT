#include "system/camera_system.h"

#include "components.h"

namespace Systems {
	CameraSystem* CameraSystem::instance = nullptr;

	//Defaults to entity 0 with position of 0,0,0. Probably should have a better value but it's okay for now.
	//Also gets the entity manager
	CameraSystem::CameraSystem() : 
		entity(-1), 
		relativePosition(Math::Vec3()), 
		entityMan(ResourceManager::EntityManager::getEntityManager()),
		componentMan(ResourceManager::ComponentManager::getComponentManager()) 
	
	{}

	CameraSystem::~CameraSystem() {
		if (instance != nullptr)
			delete instance;
	}

	CameraSystem* CameraSystem::getCameraSystem() {
		if (instance == nullptr)
			instance = new CameraSystem;

		return instance;
	}

	void CameraSystem::setEntity(std::string name) {
		this->entity = this->entityMan->getEntityID(name);
	}

	//Sets the position of the camera relative to the entity it is looking at
	void CameraSystem::setRelativePosition(Math::Vec3 relativePosition) {
		this->relativePosition = relativePosition;
	}

	unsigned int CameraSystem::getEntity() {
		return this->entity;
	}

	//Returns absolute position of the camera
	Math::Vec3& CameraSystem::getPosition() {
		//TODO
		//Better error handling!! just everywhere...

		Resources::PositionComponent& entityPosComp = this->componentMan->getComponent<Resources::PositionComponent>(this->entity);
		Math::Vec3& entityPos = entityPosComp.position;
		
		//Sets camera's position
		//Doing this math every time is problematic, buuut right now I'm just going with waht works. 
		//I'll refactor later...
		this->absolutePosition = entityPos + this->relativePosition;

		return this->absolutePosition;
	}

	Math::Matrix4 CameraSystem::getCameraViewMatrix() {
		//Entity Position
		Resources::PositionComponent& entityPosComp = this->componentMan->getComponent<Resources::PositionComponent>(this->entity);
		Math::Vec3& entityPos = entityPosComp.position;

		//Camera position
		Math::Vec3 camPosition = this->relativePosition + entityPos;

		//Forward Vector
		Math::Vec3 forward = (entityPos - camPosition).normalize();

		//Right Vector
		Math::Vec3 right = forward.cross(Math::Vec3(0, 1, 0)).normalize();

		//Up vector
		Math::Vec3 up = right.cross(forward).normalize();

		return Math::Matrix4::getViewMatrix(right, up, forward, camPosition);
	}
}
