#include <iostream>

#include "../header_files/matrix4.h"

namespace Math {
	//Constructors
	Matrix4::Matrix4(const float* data)
		: data(new float[16])
	{
		for (int i = 0; i < 16; ++i) {
			this->data[i] = data[i];
		}
	}

	Matrix4::Matrix4()
		: data(new float[16])
	{
		for (int i = 0; i < 16; ++i) {
			this->data[i] = 0;
		}
	}

	//Copy Constructor
	Matrix4::Matrix4(const Matrix4& copy)
		: data(new float[16])
	{
		for (int i = 0; i < 16; ++i) {
			this->data[i] = copy.data[i];
		}
	}

	//Move Constructors
	Matrix4::Matrix4(Matrix4&& move) noexcept
		: data(move.data)
	{
		move.data = nullptr;
	}

	//Used for inexpensive conversion from generic matrix to 4x4 matrix
	Matrix4::Matrix4(Matrix&& move) noexcept {
		if (move.getColumns() != 4 || move.getRows() != 4)
			throw MatrixIncorrectDimensionsException();

		this->data = move.data;
		move.data = nullptr;
	}

	//Destructor
	Matrix4::~Matrix4() {
		delete[] this->data;
	}

	//Getters
	float Matrix4::getData(int index) const {
		return this->data[index];
	}

	float* Matrix4::getDataPointer() const {
		return this->data;
	}

	//Setters
	void Matrix4::setData(float data, int index) {
		this->data[index] = data;
	}

	void Matrix4::setData(const float* data) {
		for (int i = 0; i < 16; ++i) {
			this->data[i] = data[i];
		}
	}

	//Print function for testing
	void Matrix4::printData() const {
		for (int i = 0; i < 16; ++i) {
			std::cout << this->getData(i) << ", ";

			if ((i + 1) % 4 == 0)
				std::cout << std::endl;
		}
	}

	//Operations
	Matrix4& Matrix4::operator=(const Matrix4& other) {
		for (int i = 0; i < 16; ++i) {
			this->setData(other.getData(i), i);
		}

		return *this;
	}

	Matrix4& Matrix4::operator=(const Matrix4&& other) noexcept {
		for (int i = 0; i < 16; ++i) {
			this->setData(other.getData(i), i);
		}

		return *this;
	}

	Matrix4 Matrix4::operator+(const Matrix4& other) const{
		Matrix4 out;

		for (int i = 0; i < 16; ++i) {
			out.setData(this->getData(i) + other.getData(i), i);
		}

		return out;
	}

	Matrix4 Matrix4::operator-(const Matrix4& other) const {
		Matrix4 out;

		for (int i = 0; i < 16; ++i) {
			out.setData(this->getData(i) - other.getData(i), i);
		}

		return out;
	}

	Matrix4 Matrix4::operator*(float scalar) const {
		Matrix4 out;

		for (int i = 0; i < 16; ++i) {
			out.setData(out.getData(i) * scalar, i);
		}

		return out;
	}

	//It's called efficiency
	Matrix4 Matrix4::operator*(const Matrix4& other) const {
		Matrix4 out;
		const float* a = this->data;
		const float* b = other.data;
		float* o = out.data;

		//Row 1
		o[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
		o[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
		o[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
		o[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];

		//Row 2
		o[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
		o[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
		o[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
		o[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];

		//Row 3
		o[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
		o[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
		o[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
		o[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];

		//Row 4
		o[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
		o[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
		o[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
		o[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];

		return out;
	}

	//TODO 
	//Maybe hardcode this for a LIL extra speed if I find I'm using it often

	//This multiples the matrix by the vector
	//Since the return is Vec4, I thoughta bout putting this in the Vec4 class, buuut
	//since the first operand has to be the matrix and it matters, it intuitively makes most sense here I think.
	Vec4 Matrix4::operator*(const Vec4& other) const {
		//Arrays with values so I can use this with my loop below
		const float valsIn[4] = { other.x(), other.y(), other.z(), other.w() };
		float valsOut[4] = {0, 0, 0, 0};
		
		for (int i = 0; i < 15; i+=4) {
			for (int j = 0; j < 4; ++j) {
				valsOut[i / 4] += this->data[i + j] * valsIn[j];
			}
		}

		return Vec4(valsOut[0], valsOut[1], valsOut[2], valsOut[3]);
	}

	//TODO Please fix these.
	/*
	* For now, the functions below will not be specified to 4x4 matrices like my multiplication was.
	* If I find that I'm doing these functions as frequently, then I will fix that, but for now, it will just
	* convert to a regular matrix and then change it back.
	*/
	Matrix4 Matrix4::transpose() const {
		Matrix temp(4, 4, this->data);

		return temp.transpose();
	}

	Matrix4 Matrix4::inverse() const {
		Matrix temp(4, 4, this->data);

		return temp.inverse();
	}

	float Matrix4::getDeterminant() const {
		const Matrix temp(4, 4, this->data);

		return temp.getDeterminant();
	}
	
	//Transformation Matrices
	//Scaling matrix
	Matrix4 Matrix4::getScaleMatrix(float xScale, float yScale, float zScale) {
		const float data[16] = { xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, zScale, 0, 0, 0, 0, 1 };

		return Matrix4(data);
	}

	//Translation matrix
	Matrix4 Matrix4::getTranslationMatrix(float xTranslate, float yTranslate, float zTranslate) {
		const float data[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, xTranslate, yTranslate, zTranslate, 1};

		return Matrix4(data);
	}

	//Quaternion rotation matrix
	Matrix4 Matrix4::getQRotationMatrix(Vec3 axis, float angle) {
		//The math here is derived from quaternion rotation operator
		//As well as quaternion multiplication, using the definition i^2 = j^2 = k^2 = ijk = -1
		//Also knowing that to rotate a point, you multiply qpq^-1
		//More information here: https://www.songho.ca/opengl/gl_quaternion.html

		axis = axis.normalize();

		const float s = std::cos(angle / 2.0);
		const float x = std::sin(angle / 2.0) * axis.x();
		const float y = std::sin(angle / 2.0) * axis.y();
		const float z = std::sin(angle / 2.0) * axis.z();

		//Accidentally put row major but keeping it just in case
		/*const float data[16] = {
			1.0 - 2.0*y*y - 2.0*z*z, 2.0*x*y - 2.0*s*z, 2.0*x*z + 2.0*s*y, 0,
			2.0*x*y + 2.0*s*z, 1.0 - 2.0*x*x - 2.0*z*z, 2.0*y*z - 2.0*s*x, 0,
			2.0*x*z - 2.0*s*y, 2.0*y*z + 2.0*s*x, 1.0 - 2.0*x*x - 2.0*y*y, 0,
			0, 0, 0, 1
		};*/

		const float data[16] = {
			1.0 - 2.0*y*y - 2.0*z*z, 2.0*x*y + 2.0*s*z, 2.0*x*z - 2.0*s*y, 0,
			2.0*x*y - 2.0*s*z, 1 - 2.0*x*x - 2.0*z*z, 2.0*y*z + 2.0*s*x, 0,
			2.0*x*y + 2.0*s*y, 2.0*y*z - 2.0*s*x, 1 - 2.0*x*x - 2.0*y*y, 0,
			0, 0, 0, 1
		};

		return Matrix4(data);
	}

	//Euler roation matrix
	Matrix4 Matrix4::getERotationMatrix(float xRot, float yRot, float zRot) {
		float xDat[16] = {
			1, 0, 0, 0, 
			0, std::cos(xRot), -1.0 * std::sin(xRot), 0,
			0, std::sin(xRot), std::cos(xRot), 0,
			0, 0, 0, 1
		};

		float yDat[16] = {
			std::cos(yRot), 0, std::sin(yRot), 0,
			0, 1, 0, 0, 
			-1.0 * std::sin(yRot), 0, std::cos(yRot), 0, 
			0, 0, 0, 1
		};

		float zDat[16]{
			std::cos(zRot), std::sin(zRot), 0, 0,
			-1.0 * sin(zRot), std::cos(zRot), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		return Matrix4(xDat) * Matrix4(yDat) * Matrix4(zDat);
	}

	//OpenGL matrices
	Matrix4 Matrix4::getModelMatrix(const Vec3& position, const Vec3& rotation, const Vec3& scale) {
		Matrix4 t(Matrix4::getTranslationMatrix(position.x(), position.y(), position.z()));
		Matrix4 e(Matrix4::getERotationMatrix(rotation.x(), rotation.y(), rotation.z()));
		Matrix4 s(Matrix4::getScaleMatrix(scale.x(), scale.y(), scale.z()));

		return s * e * t;
	}

	Matrix4 Matrix4::getViewMatrix(const Vec3& cameraRight, const Vec3& cameraUp, const Vec3& cameraFront, const Vec3& cameraPosition) {
		//Change of basis formula
		float dat[16] = {cameraRight.x(), cameraUp.x(), -cameraFront.x(), 0,
						cameraRight.y(), cameraUp.y(), -cameraFront.y(), 0,
						cameraRight.z(), cameraUp.z(), -cameraFront.z(), 0,
						-cameraRight.dot(cameraPosition), -cameraUp.dot(cameraPosition), cameraFront.dot(cameraPosition), 1 };
		
		/*float dat[16] = {cameraRight.x(), cameraRight.y(), cameraRight.z(), -cameraRight.dot(cameraPosition),
						cameraUp.x(), cameraUp.y(), cameraUp.z(), -cameraUp.dot(cameraPosition), 
						-cameraFront.x(), -cameraFront.y(), -cameraFront.z(), cameraFront.dot(cameraPosition),
						0, 0, 0, 1};*/

		return Matrix4(dat);
	}

	Matrix4 Matrix4::getProjectionMatrix() {
		//I found this math from here http://www.songho.ca/opengl/gl_projectionmatrix.html
		//I am not yet sure if this will change based on other things but for now im just going simple.

		float n = 0.01;
		float t = n * std::tan(1.5/2.0);
		float b = -1 * t;
		float r = t * 6.0/8.0;
		float l = -1 * r;
		float f = 1000;

		//Row major reprentation cuz I'm a goofy dumbass
		/*float dat[16] = {(2.0 * n) / (r - l), 0, (r + l) / (r - l), 0,
						0, (2.0 * n) / (t - b), (t + b) / (t - b), 0,
						0, 0, (-1.0 * (f + n)) / (f - n), (-2.0 * f * n) / (f - n),
						0, 0, -1, 0 };*/

		float dat[16] = {(2.0 * n) / (r - l), 0, 0, 0,
				0, (2.0 * n)/(t - b), 0, 0,
				(r + l)/(r - l), (t + b)/(t - b), (-1.0 * (f + n))/(f - n), -1,
				0, 0, (-2.0 * n * f)/(f - n), 0};

		return Matrix4(dat);
	}
}