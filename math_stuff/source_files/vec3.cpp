#include "../header_files/vec3.h"
#include <iostream>

#include "../exceptions/math_exceptions.h"
#include "../header_files/quaternion.h"

namespace Math {
	//Constructors
	Vec3::Vec3(float x, float y, float z) 
		: xVal(x), yVal(y), zVal(z) { }

	Vec3::Vec3() 
		: xVal(0), yVal(0), zVal(0) { }

	//Getters
	float Vec3::x() const {
		return this->xVal;
	}

	float Vec3::y() const {
		return this->yVal;
	}

	float Vec3::z() const {
		return this->zVal;
	}

	//Setters
	void Vec3::setX(float x) {
		this->xVal = x;
	}

	void Vec3::setY(float y) {
		this->yVal = y;
	}

	void Vec3::setZ(float z) {
		this->zVal = z;
	}

	//Addition operator
	Vec3 Vec3::operator+ (const Vec3& other) const{
		float x = this->x() + other.x();
		float y = this->y() + other.y();
		float z = this->z() + other.z();

		return Vec3(x, y, z);
	}

	//Addition operator
	Vec3 Vec3::operator- (const Vec3& other) const {
		float x = this->x() - other.x();
		float y = this->y() - other.y();
		float z = this->z() - other.z();

		return Vec3(x, y, z);
	}

	//Scalar multiplication
	Vec3 Vec3::operator* (float scalar) const {
		float x = this->x() * scalar;
		float y = this->y() * scalar;
		float z = this->z() * scalar;

		return Vec3(x, y, z);
	}

	//Cross product
	Vec3 Vec3::cross(const Vec3& other) const {
		Vec3 out;

		float outX = (this->y() * other.z()) - (this->z() * other.y());
		float outY = -1 * ((this->x() * other.z()) - (this->z() * other.x()));
		float outZ = (this->x() * other.y()) - ((this->y() * other.x()));

		out.setX(outX);
		out.setY(outY);
		out.setZ(outZ);

		return out;
	}

	//Normalize the Vector
	Vec3 Vec3::normalize() const {
		Vec3 out;

		float x = this->x();
		float y = this->y();
		float z = this->z();

		float length = (x * x) + (y * y) + (z * z);
		length = std::sqrt(length);

		out.setX(this->x()/length);
		out.setY(this->y()/length);
		out.setZ(this->z()/length);

		return out;
	}

	//Returns dot product
	float Vec3::dot(const Vec3& other) const {
		return (this->x() * other.x()) + (this->y() * other.y()) + (this->z() * other.z());
	}

	//Turns vector into quaternion. Used mostly for rotations. 
	Quaternion Vec3::toQuaternion() const {
		Quaternion out = Quaternion(0, this->x(), this->y(), this->z());
		return out;
	}
}