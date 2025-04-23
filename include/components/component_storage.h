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

	//Returns reference to component of type T belonging to entity
	template <typename T>
	T& ComponentStorage<T>::getComponent(const unsigned int entity) {
		//I should have better error handling here but for now I'll assume this exists
		return this->components[entity];
	}

	//Adds component to entity
	template <typename T>
	void ComponentStorage<T>::addComponent(T component, unsigned int entity) {

		/*
		* TODO:
		* I wrote this and MOST of my other objects with the assumption
		* that the scope of the component the user adds will change, so this
		* and many other objects I have create copies (such as this one) rather
		* than transferring ownership. I would like to implement move semantics
		* for things like this rather than creating deep copies in the future.
		* This applies to like any class I instantiate.
		* The compiler probably optimizes this anyway but its still worth mentioning
		* I'm only gonna write this out once.
		*/
		//Same deal as above
		this->components[entity] = component;
	}

	//Returns false if the specified component for the entity does not exist, and true otherwise
	template <typename T>
	bool ComponentStorage<T>::hasComponent(unsigned int entity) {
		return this->components.count(entity); //0 if its not there, 1 if it is
	}
}

#endif 