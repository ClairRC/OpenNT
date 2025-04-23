#ifndef texture_component_h
#define texture_component_h

#include "components/i_component.h"

namespace Resources {
	//Component that stores information for textures
	struct TextureComponent : IComponent {
		//There is a significant amount of texture customization options that I should
		//include here, but because I need a prototype by uhhh yesterday, I am
		//keeping it simple and general
		std::string name;
	};
}

#endif