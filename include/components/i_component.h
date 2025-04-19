#ifndef i_component_h
#define i_component_h

#include <iostream>

namespace Resources {
	struct IComponent {
		virtual ~IComponent() = 0;
	};
}

#endif