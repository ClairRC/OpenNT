#include <cmath>

#include "math_stuff/vec.h"
#include "math_stuff/matrix.h"
#include "math_stuff/VectorIndexOutOfBoundsException.h"
#include "math_stuff/VectorIncorrectDimensionsException.h"

namespace Math {
	//Constructors
	Vec::Vec(size_t size) 
		: size(size), data(new float[size]) {
		
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = 0;
		}
	}

	Vec::Vec(size_t size, const float* data) 
		: size(size), data(new float[size]) {

		this->setData(data);
	}

	//Copy constructor
	Vec::Vec(const Vec& copy)
		: size(copy.getSize()), data(new float[copy.getSize()])
	{
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = copy.data[i];
		}
	}

	//Move cosntructor
	Vec::Vec(Vec&& move) noexcept
		: size(move.getSize()), data(move.data)
	{
		move.data = nullptr;
		move.size = 0;
	}

	//Destructor
	Vec::~Vec() {
		delete[] this->data;
	}

	//Public functions
	//Getters
	float Vec::getData(int index) const {
		if (index >= size) {
			throw Math::VectorIndexOutOfBoundsException();
		}

		return data[index];
	}

	size_t Vec::getSize() const {
		return size;
	}

	//Setters
	//TODO: Better error handling here
	void Vec::setData(const float* data) {
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = data[i];
		}
	}

	//Vector operations
	void Vec::setData(float data, int index) {
		if (index >= this->size)
			throw VectorIndexOutOfBoundsException();

		this->data[index] = data;
	}

	//Assignment operators because I'm dealing with funny raw pointers
	//Debatably bad idea but again, it makes the most sense for my purposes... But
	//there's a lot more workaround than I thought there'd be. Lesson learned.
	Vec& Vec::operator= (const Vec& other) {
		//If sizes are different, still allow assignment
		if (other.getSize() != this->getSize()) {
			this->size = other.getSize();
			delete[] this->data;
			
			this->data = new float[other.getSize()];
		}

		for (int i = 0; i < other.getSize(); ++i) {
			this->setData(other.getData(i), i);
		}
		
		return *this;
	}

	//Allows adding an rvalue (such as a=b+c) just for my convenience
	Vec& Vec::operator= (const Vec&& other) noexcept {
		//If sizes are different, still allow assignment
		if (other.getSize() != this->getSize()) {
			this->size = other.getSize();
			delete[] this->data;

			this->data = new float[other.getSize()];
		}

		for (int i = 0; i < other.getSize(); ++i) {
			this->setData(other.getData(i), i);
		}

		return *this;
	}

	//Addition operator
	Vec Vec::operator+ (const Vec& other) const {
		if (this->size != other.size)
			throw Math::VectorIncorrectDimensionsException();

		Vec out(this->size);

		for (int i = 0; i < out.size; ++i) {
			out.data[i] = this->data[i] + other.data[i];
		}

		return out;
	}

	//Subtraction operator
	Vec Vec::operator- (const Vec& other) const {
		if (this->size != other.size)
			throw Math::VectorIncorrectDimensionsException();

		Vec out(this->size);

		for (int i = 0; i < out.size; ++i) {
			out.data[i] = this->data[i] - other.data[i];
		}

		return out;
	}

	//Scalar multiplication
	Vec Vec::operator* (float scalar) const {
		Vec out(this->size);

		for (int i = 0; i < out.size; ++i) {
			out.data[i] = this->data[i] * scalar;
		}

		return out;
	}

	//Dot product
	float Vec::dot(Vec& other) const {
		if (this->size != other.size)
			throw Math::VectorIncorrectDimensionsException();

		float out = 0.0f;

		for (int i = 0; i < this->size; ++i) {
			out += this->data[i] * other.data[i];
		}

		return out;
	}

	//Normalize vector
	Vec Vec::normalize() const {
		Vec out(this->size);

		float magnitude = this->getMagnitude();

		for (int i = 0; i < out.size; ++i) {
			out.data[i] = this->data[i] / magnitude;
		}

		return out;
	}

	//Returns magnitude
	float Vec::getMagnitude() const {
		float magnitude = 0;

		for (int i = 0; i < this->size; ++i) {
			magnitude += this->data[i] * this->data[i];
		}

		magnitude = std::sqrt(magnitude);

		return magnitude;
	}

	//Transform to matrix. Not sure if I'll need these (mostly the row one) but while I'm here.
	Matrix Vec::toColumnMatrix() const{
		return Matrix(this->getSize(), 1, this->data);
	}

	Matrix Vec::toRowMatrix() const {
		return Matrix(1, this->getSize(), this->data);
	}
}