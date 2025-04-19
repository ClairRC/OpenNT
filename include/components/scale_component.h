#ifndef scale_component_h
#define scale_component_h

#include "components/i_component.h"
#include "math_stuff.h"

namespace Resources {
	struct ScaleComponent : IComponent {
		Math::Vec3 scales;
	};
}

#endif 
