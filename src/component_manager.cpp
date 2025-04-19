#include "resource_manager/component_manager.h"

namespace ResourceManager {

	ComponentManager* ComponentManager::instance = nullptr;

	ComponentManager::ComponentManager() { }

	ComponentManager::~ComponentManager() {
		if (instance != nullptr)
			delete instance;
	}

	ComponentManager* ComponentManager::getComponentManager() {
		if (instance == nullptr) {
			instance = new ComponentManager();
		}

		return instance;
	}

}