#ifndef camera_system_h
#define camera_system_h

#include "math_stuff.h"
#include "resource_manager.h"

namespace Systems {
	/*
	* Realistically this camera is nothing more than the entity that should be followed
	* and the distance from that entity that the camera will watch from.
	* So realistically, the camera iself doesn't "move", moreso the entity it watches moves and the camera just follows.
	* My dilemma is if the camera entity changes, I would want it to smoothly 'move' to the other entity, uuuh
	* but I'll cross that bridge when I get there. For now, this will follow 1 entity that is presumed to be the 
	* player character, and however that moves the camera SHOULD follow.
	* 
	* TODO:
	* This shouldn't be lumped with the "systems", but I'll keep it here for now. It doesn't really matter anyway
	* This is also kind of a weird way to define a camera. The camera is nothing more than a position and direction,
	* but I could probably implement this in a less confusing way. It works for now though.
	*/
	class CameraSystem {
	private:
		//These define where the camera is compared to the entity it is anchored to
		unsigned int entity; //Entity the camera watches
		Math::Vec3 relativePosition; //Position compared to the entity
		Math::Vec3 absolutePosition;

		//Singleton so no copying or moving
		CameraSystem(const CameraSystem& copy) = delete;
		CameraSystem(CameraSystem&& move) noexcept = delete;

		//Constructor
		CameraSystem();

		static CameraSystem* instance; //Singleton pointer
		ResourceManager::EntityManager* entityMan; //Pointer to entity manager reference
		ResourceManager::ComponentManager* componentMan; //Pointer to component manager

	public:
		//Destructor
		~CameraSystem();

		//Returns instance
		static CameraSystem* getCameraSystem();

		//Sets camera focus and position compared to it.
		void setEntity(const std::string name);
		void setRelativePosition(const Math::Vec3 position);

		//Gets information which the render system will use to. render.
		unsigned int getEntity();
		Math::Vec3& getPosition();
		Math::Matrix4 getCameraViewMatrix();
	};
}

#endif 