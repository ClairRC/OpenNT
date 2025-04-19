#ifndef movement_component_h
#define movement_component_h

#include "components/i_component.h"
#include "math_stuff.h"

//Very band-aid and rushed hard-coding approach to movement
//But thats because I'm running out of time. I will fix this in the future.
namespace Resources {
	//Movement component to decide if something moves when the arrow keys are pressed'
	struct MovementComponent : IComponent {
		float movementSpeed;
	};
}

#endif 