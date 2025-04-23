#include "resource_manager/entity_manager.h"

namespace ResourceManager {
	EntityManager* EntityManager::instance = nullptr;

	EntityManager::EntityManager() : numEntities(0) { }

	EntityManager::~EntityManager() {
		if (instance != nullptr)
			delete instance;
	}

	EntityManager* EntityManager::getEntityManager() {
		if (instance == nullptr) {
			instance = new EntityManager();
		}

		return instance;
	}

	void EntityManager::createEntity(std::string name) {
		//I am going to have this overwrite if two entities use the same name for now
		if (this->entityList.count(name) > 0) {
			//TODO!!
			//If entity gets overwritten it needs to have its components deleted!
			std::cerr << "Entity already exists. It will be overwritten." << std::endl;
		}

		this->entityList[name] = this->numEntities;
		++this->numEntities;
	}

	//Returns the ID of an entity given the string
	unsigned int EntityManager::getEntityID(std::string name) {
		//If entity name isn't found, return -1
		//Dumb inconsistent handling of errors!!!!!! my code sucks!!!!
		if (this->entityList.count(name) == 0)
			return -1;

		return this->entityList[name];
	}

	//This returns a reference to the list of entities. Ideally I make this better encapsulated but I need it elsewhere.
	std::map<std::string, unsigned int>& EntityManager::getEntityList() {
		return this->entityList;
	}
}