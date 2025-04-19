#ifndef position_component_h
#define position_component_h

#include "components/i_component.h"
#include "math_stuff.h"

namespace Resources {
	struct PositionComponent : Resources::IComponent {
		Math::Vec3 position;
	};
}

#endif 