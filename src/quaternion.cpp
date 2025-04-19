#include "math_stuff/quaternion.h"

namespace Math {
	//Constructor
	Quaternion::Quaternion(float w, float x, float y, float z) : wVal(w), xVal(x), yVal(y), zVal(z) { }
	
	//Default Constructor
	Quaternion::Quaternion() : wVal(0), xVal(0), yVal(0), zVal(0) {}

	//Getters
	float Quaternion::w() const {
		return this->wVal;
	}

	float Quaternion::x() const {
		return this->xVal;
	}

	float Quaternion::y() const {
		return this->yVal;
	}

	float Quaternion::z() const {
		return this->zVal;
	}

	//Setters
	void Quaternion::setW(float w) {
		this->wVal = w;
	}

	void Quaternion::setX(float x) {
		this->xVal = x;
	}

	void Quaternion::setY(float y) {
		this->yVal = y;
	}

	void Quaternion::setZ(float z) {
		this->zVal = z;
	}

	//Operator Overload
	//Quaternion addition (easy)
	Quaternion Quaternion::operator+ (const Quaternion& other) const {
		Quaternion out = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

		out.setW(this->w() + other.w());
		out.setX(this->x() + other.x());
		out.setY(this->y() + other.y());
		out.setZ(this->z() + other.z());

		return out;
	}

	//Quaterion Multiplication is. STUPID! :D
	//This comes from the definition of i^2=j^2=k^2=ijk=-1
	Quaternion Quaternion::operator* (const Quaternion & other) const {
		Quaternion out = Quaternion();

		float outW =
			(this->w() * other.w()) -
			(this->x() * other.x()) -
			(this->y() * other.y()) -
			(this->z() * other.z());

		float outX =
			(this->w() * other.x()) +
			(this->x() * other.w()) +
			(this->y() * other.z()) -
			(this->z() * other.y());

		float outY =
			(this->w() * other.y()) -
			(this->x() * other.z()) +
			(this->y() * other.w()) +
			(this->z() * other.x());

		float outZ =
			(this->w() * other.z()) +
			(this->x() * other.y()) -
			(this->y() * other.x()) +
			(this->z() * other.w());

		out.setW(outW);
		out.setX(outX);
		out.setY(outY);
		out.setZ(outZ);

		return out;
	};

	//Returns vector representation for the vector part of the quaternion
	//I am still not sure if I will need this
	Vec3 Quaternion::getVector() const {
		Vec3 out;

		out.setX(this->x());
		out.setY(this->y());
		out.setZ(this->z());

		return out;
	}

	Quaternion Quaternion::getInverse() const {
		float magSquared = this->getMagnitude();
		magSquared *= magSquared;

		float w = this->wVal / magSquared;
		float x = ( -1 * this->xVal) / magSquared;
		float y = (-1 * this->yVal) / magSquared;
		float z = (-1 * this->zVal) / magSquared;

		Quaternion out = Quaternion(w, x, y, z);

		return out;
	}

	float Quaternion::getMagnitude() const {
		float mag = (this->wVal * this->wVal) + (this->xVal * this->xVal) + (this->yVal * this->yVal) + (this->zVal * this->zVal);
		mag = std::sqrt(mag);

		return mag;
	}
}