#ifndef entity_manager_h
#define entity_manager_h

#include <iostream>
#include <map>

namespace ResourceManager {
	//Singleton class to create and remove entites and their components
	class EntityManager {
	private:
		EntityManager();

		//Deleting theses constructors because this is a singleton clas
		EntityManager(const EntityManager& copy) = delete;
		EntityManager(EntityManager&& move) noexcept = delete;

		static EntityManager* instance;
		std::map<std::string, unsigned int> entityList;
		unsigned int numEntities;

	public:
		~EntityManager();
		static EntityManager* getEntityManager();

		void createEntity(std::string name);
		unsigned int getEntityID(std::string name);
		std::map<std::string, unsigned int>& getEntityList();
	};
}

#endif 