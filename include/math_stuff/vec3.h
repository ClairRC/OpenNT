#ifndef vec3_h
#define vec3_h

#include <iostream>

namespace Math {
	//Foward Decarations
	class Quaternion;

	//3D vector Class
	/*
	* Initially I was going to make this a subclass, but I think
	* for my purposes that just makes a little less sense. My Vec class already
	* is scary with memory management, so no need to make that worse, plus I don't really
	* gain anything since I'm not really inheriting anything useful or overriding anything.
	* Plus being able to enforce Vec3/4 will trade runtime errors for compiler errors
	* which I think is definitely advantageos.
	*/
	class Vec3 {
	//Private members
	private:
		float xVal;
		float yVal;
		float zVal;

	//Public stuff
	public:
		//Constructors
		Vec3(float x, float y, float z);
		Vec3();

		//Getters
		float x() const;
		float y() const;
		float z() const;

		//Setters
		void setX(float x);
		void setY(float y);
		void setZ(float z);

		//Operations
		Vec3 operator+ (const Vec3& other) const;
		Vec3 operator- (const Vec3& other) const;
		Vec3 operator* (float scalar) const;
		Vec3 cross(const Vec3& other) const;
		Vec3 normalize() const;
		float dot(const Vec3& other) const;

		Quaternion toQuaternion() const;
	};
}
#endif