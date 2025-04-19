#ifndef color_component_h
#define color_component_h

#include "components/i_component.h"
#include "math_stuff.h"

namespace Resources {
	struct ColorComponent : Resources::IComponent {
		Math::Vec4 color;
	};
}

#endif 