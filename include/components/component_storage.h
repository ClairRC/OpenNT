#ifndef component_storage_h
#define component_storage_h

#include "components/i_component.h"
#include "components/i_component_storage.h"
#include <iostream>
#include <unordered_map>

namespace ResourceManager {
	template <typename T>
	class ComponentStorage : public IComponentStorage {
	private:
		std::unordered_map<unsigned int, T> components;

	public:
		//TODO 
		//Relearn how to make this a friend for componemnt manager so this isnt publically available

		T& getComponent(unsigned int entity);
		void addComponent(T component, unsigned int entity);
		bool hasComponent(unsigned int entity);
	};

	//Template function definitions!!
	//Still not sure why these can only exist here but whatever
	template <typename T>
	T& ComponentStorage<T>::getComponent(const unsigned int entity) {
		//I should have better error handling here but for now I'll assume this exists
		return this->components[entity];
	}

	template <typename T>
	void ComponentStorage<T>::addComponent(T component, unsigned int entity) {
		//Same deal as above
		this->components[entity] = component;
	}

	template <typename T>
	bool ComponentStorage<T>::hasComponent(unsigned int entity) {
		return this->components.count(entity); //0 if its not there, 1 if it is
	}
}

#endif 