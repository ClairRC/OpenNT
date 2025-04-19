#ifndef light_source_component_h
#define light_source_component_h

#include "components/i_component.h"
#include "math_stuff.h"

namespace Resources {
	struct LightSourceComponent : IComponent {
		Math::Vec3 lightColor;
		Math::Vec3 lightPos;
	};
}

#endif 