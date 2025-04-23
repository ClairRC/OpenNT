#ifndef component_manager_h
#define component_manager_h

#include "components.h"
#include "resource_manager/entity_manager.h"

#include <memory>
#include <iostream>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>


/*
* TODO:
* So a LOT of my classes are implemented as a singleton which is kind of a mess for
* global resource management. I would like to change this so that these things are more specific
* for different scenes, which will make resource deletion and aquisition and caching so much
* more convenient. This applies to nearly (but not all) of my singleton classes
*/
namespace ResourceManager {
	class ComponentManager {
	private:
		ComponentManager();

		//Singleton class so NO copy or move semantics
		ComponentManager(const ComponentManager& copy) = delete;
		ComponentManager(ComponentManager&& move) noexcept = delete;

		//Gets a reference to the storage class for component of T type
		template <typename T>
		ComponentStorage<T>& getStorage();

		//Map that stores each component type as a key and then another map as a value, which stores the entity and the component pointer
		//Kiiinda confusing but allows for the ability to create new components without editing this manager
		static ComponentManager* instance;
		std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> storages;

	public:
		~ComponentManager();
		static ComponentManager* getComponentManager();

		template <typename T>
		void addComponent(T component, const std::string entityName);

		template <typename T>
		bool entityHasComponent(unsigned int entityID);

		template <typename T>
		T& getComponent(unsigned int entityID);

		template <typename T>
		T& getComponent(std::string entityName);
	};

	//Template function definitions
	template <typename T>
	ComponentStorage<T>& ComponentManager::getStorage() {
		std::type_index tType(typeid(T));

		//If this type has not been stored yet..
		if (this->storages.count(tType) == 0) {
			//Put it in
			this->storages[tType] = std::make_unique<ComponentStorage<T>>();
		}

		//Not sure exactly how static/dynamic casting works, but I'm going with it
		return *static_cast<ComponentStorage<T>*>(this->storages[tType].get());
	}

	template <typename T>
	void ComponentManager::addComponent(T component, const std::string entityName) {
		//Get entity
		ResourceManager::EntityManager* entityManager = ResourceManager::EntityManager::getEntityManager();
		unsigned int entity = entityManager->getEntityID(entityName);

		ComponentStorage<T>& storage = this->getStorage<T>();

		storage.addComponent(component, entity);
	}

	template <typename T>
	bool ComponentManager::entityHasComponent(unsigned int entityID) {
		std::type_index tType(typeid(T));
		//If this type is not currently stored, then return false
		if (this->storages.count(tType) == 0)
			return false;

		ComponentStorage<T>& storage = this->getStorage<T>();

		return storage.hasComponent(entityID); //0 for no, 1 for yes
	}

	template <typename T>
	T& ComponentManager::getComponent(unsigned int entityID) {
		ComponentStorage<T>& storage = this->getStorage<T>();

		return storage.getComponent(entityID);
	}

	template <typename T>
	T& ComponentManager::getComponent(std::string entityName) {
		//""no matching overload function found"" wanna bet???
		//I'm sure its my fault but its like literally 5 lines up

		//Get entity
		ResourceManager::EntityManager* entityManager = ResourceManager::EntityManager::getEntityManager();
		unsigned int entity = entityManager->getEntityID(entityName);

		ComponentStorage<T>& storage = this->getStorage<T>();

		return storage.getComponent(entity);
	}
}

#endif 