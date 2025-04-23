#ifndef render_system_h
#define render_system_h

#include "resource_manager.h"
#include "system/camera_system.h"

/*
* TODO:
* This class is the core of my issues at the moment. I've tried really hard to have
* modular and scalable architecture and I think I succeeded in a lot of ways, but anything
* in the Systems namespace needs to just be re-thought out.
* I think that I am going to have a middle-man kinda controller kinda deal that
* can be the data collector so that the systems don't have to get all spaghetti 
* trying to retrieve the data necessary for rendering (or whatever else the system is doing).
* I think I will implement controller classes that have structs to store the necessary data
* that it will pass to the systems when necessary, which should help a loot with the scalability.
* I would love to write even more about how much the organization of this class (and any other 
* System class) bugs me, but instead I'll just fix it whenever the time comes.
*/

namespace Systems {
	class RenderSystem {
	private:
		//Manager instances to get needed data
		static ResourceManager::ComponentManager* componentManager;
		static ResourceManager::VAOManager* vaoManager;
		static Systems::CameraSystem* cameraSystem;
		static ResourceManager::TextureManager* textureManager;

		//Struct for transformation vectors
		struct transformations {
			Math::Vec3 position;
			Math::Vec3 rotation;
			Math::Vec3 scales;
		};

		//Helper functions for rendering specific things
		static transformations getTransformations(unsigned int entity);
		static void passMVPMatrices(unsigned int shader, Math::Matrix4& model, Math::Matrix4& view, Math::Matrix4& projection);
		static void passTextureInfo(unsigned int entity);

	public: 
		//Don't want this instantiated!!!
		RenderSystem() = delete;
		RenderSystem(RenderSystem& copy) = delete;
		RenderSystem(RenderSystem&& move) noexcept = delete;

		static void renderEntities(); //Right now this renders everything, buuut I should make it better eventually..
	};
}

#endif