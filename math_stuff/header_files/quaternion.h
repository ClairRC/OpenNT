#ifndef quaternion_h
#define quaternion_h

#include "vec3.h"

namespace Math {
	//Quaternion Class
	class Quaternion {

	//Private Fields
	private:
		//I'm using 4 floats instead of an array here
		//Just cuuuz Quaternions always have 4 members and
		//I don't wanna risk memory leaks more than I have to.
		//Plus, I won't be passing these into OpenGL or multiplying by matrices, so they 
		//can have a different structures and its fine.
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