#ifndef i_component_storage_h
#define i_component_storage_h

namespace ResourceManager {
	//Interface for component storage. This allows the component manager to store
	//and retrieve generic components given the entity id
	class IComponentStorage {
	public:
		inline virtual ~IComponentStorage() {};
	};
}

#endif 