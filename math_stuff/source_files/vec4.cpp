#include "../header_files/vec4.h"
#include <iostream>

#include "../exceptions/math_exceptions.h"

namespace Math {
	//Constructors
	Vec4::Vec4(float x, float y, float z, float w)
		: xVal(x), yVal(y), zVal(z), wVal(w) { }

	Vec4::Vec4()
		: xVal(0), yVal(0), zVal(0), wVal(0) { }

	//Getters
	float Vec4::x() const {
		return this->xVal;
	}

	float Vec4::y() const {
		return this->yVal;
	}

	float Vec4::z() const {
		return this->zVal;
	}

	float Vec4::w() const {
		return this->wVal;
	}

	//Setters
	void Vec4::setX(float x) {
		this->xVal = x;
	}

	void Vec4::setY(float y) {
		this->yVal = y;
	}

	void Vec4::setZ(float z) {
		this->zVal = z;
	}

	void Vec4::setW(float w) {
		this->wVal = w;
	}

	//Addition operator
	Vec4 Vec4::operator+ (const Vec4& other) const {
		float x = this->x() + other.x();
		float y = this->y() + other.y();
		float z = this->z() + other.z();
		float w = this->w() + other.w();
		
		return Vec4(x, y, z, w);
	}

	//Addition operator
	Vec4 Vec4::operator- (const Vec4& other) const {
		float x = this->x() - other.x();
		float y = this->y() - other.y();
		float z = this->z() - other.z();
		float w = this->w() - other.w();

		return Vec4(x, y, z, w);
	}

	//Scalar multiplication
	Vec4 Vec4::operator* (float scalar) const {
		float x = this->x() * scalar;
		float y = this->y() * scalar;
		float z = this->z() * scalar;
		float w = this->w() * scalar;

		return Vec4(x, y, z, w);
	}

	//Normalize the Vector
	Vec4 Vec4::normalize() const {
		Vec4 out;

		float x = this->x();
		float y = this->y();
		float z = this->z();
		float w = this->w();

		float length = (x * x) + (y * y) + (z * z) + (w * w);
		length = std::sqrt(length);

		out.setX(this->x() / length);
		out.setY(this->y() / length);
		out.setZ(this->z() / length);
		out.setW(this->w() / length);

		return out;
	}

	//Returns dot product
	float Vec4::dot(const Vec4& other) const {
		return (this->x() * other.x()) + (this->y() * other.y()) + (this->z() * other.z()) + (this->w() * other.w());
	}
}