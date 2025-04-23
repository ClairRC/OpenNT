#ifndef quaternion_h
#define quaternion_h

#include <iostream>

#include "math_stuff/vec3.h"

namespace Math {
	//Quaternion Class
	class Quaternion {

	//Private Fields
	private:
		//I'm using 4 floats instead of an array here
		//Just cuz Quaternions always have 4 members and
		//I don't wanna risk memory leaks more than I have to.
		//Plus, I won't be passing these into OpenGL or multiplying by matrices, so they 
		//can have a different structures and its fine.
		
		//ME FROM THE FUTURE! THE PERSON ABOVE IS DUMB.
		//ideally these matrix/vector/quaternion classes should be implemented
		//as structs because being laid out in memory together is so much cleaner 
		//for OpenGL purposes. GLM, which is a OpenGL math library does it this way
		//and I see why.
		float wVal;
		float xVal;
		float yVal;
		float zVal;

		float getMagnitude() const; //Private because I only need this for inverse function

	//Public Stuff
	public:
		//Constructors
		Quaternion(float w, float x, float y, float z);
		Quaternion();

		//Getters
		float w() const;
		float x() const;
		float y() const;
		float z() const;

		//Setters
		void setW(float w);
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		//Operations
		Quaternion operator+ (const Quaternion& other) const;
		Quaternion operator* (const Quaternion& other) const;

		//Returns the vector part of the Quaternion. I'm not yet sure if I'll ever need this but I'm adding it
		//Just In Case
		Vec3 getVector() const;
		
		//Invert quaternion mostly for rotations
		Quaternion getInverse() const;
	};
}
#endif