#ifndef rotation_component_h
#define rotation_component_h

#include "components/i_component.h"
#include "math_stuff.h"

namespace Resources {
	struct RotationComponent : IComponent {
		//For now, this is only gonna have euler rotations for simplicity
		//Quaternion rotations coming soon when I find out their use cases
		Math::Vec3 eRotation;
	};
}

#endif
