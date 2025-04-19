#ifndef render_system_h
#define render_system_h

#include "resource_manager.h"
#include "system/camera_system.h"

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