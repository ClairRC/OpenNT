#ifndef lighting_system_h
#define lighting_system_h

#include "math_stuff.h"

//Yet another thrown togeher class just to demonstrate my plans to scale and
//to not look like a dummy when my prototype has no special viewing effect at ALL

/*
* So this lighting system is bad for a number of reasons. First, it will only send in the first
* entity that has a lighting component to the shader, instead of... all of them. But again, this is just temporary,
* and building this in the first place is going to help with my ability to scale and fix it.
* Second, this is will get run every frame, which I guess is actually not an issue cuz the lighting can change,
* but it can still be costly if I expand too much. I'm still not sure how updating the position will work.
* That will likely be yet another band-aid fix that will have to change, but ya we'll see.
*/
namespace Systems {
	class LightingSystem {
	private: 
		//No instantiation...
		LightingSystem() = delete;
		LightingSystem(const LightingSystem& copy) = delete;
		LightingSystem(LightingSystem&& move) noexcept = delete;

		static Math::Vec3 frameLightColor;
		static Math::Vec3 frameLightPosition;

	public:
		static void calculateLighting();
		static Math::Vec3& getFrameLightColor();
		static Math::Vec3& getFrameLightPosition();
	};
}

#endif 