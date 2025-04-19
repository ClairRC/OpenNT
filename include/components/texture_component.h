#ifndef texture_component_h
#define texture_component_h

#include "components/i_component.h"

namespace Resources {
	//Component that stores information for textures
	struct TextureComponent : IComponent {
		//I should probably also have things like.. texture coordinates and all that
		//But for now I'm going with the basic case and assuming the texture coords will be at the corners
		//Which might be a bad assumption.
		std::string name;
	};
}

#endif