#ifndef movement_system_h
#define movement_system_h

//Okay let me be so for real with you, this whole movement system is going to
//be stitched together due to lack of time to think it through better
//I would like to have better abstractions here with a system for event handling

#include <GLFW/glfw3.h>

namespace Systems {
	class MovementSystem {
	private:
		//No instantiation or anything for now
		MovementSystem() = delete;
		MovementSystem(const MovementSystem& copy) = delete;
		MovementSystem(MovementSystem&& move) noexcept = delete;
	
	public:
		//Updates movement if it has the movement component
		static void processMovement(GLFWwindow* window);
	};
}

#endif