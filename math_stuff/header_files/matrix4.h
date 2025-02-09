#ifndef matrix4_h
#define matrix4_h

#include "vec4.h"
#include "vec3.h"
#include "matrix.h"

namespace Math {

	//4x4 matrix class
	//Primarily for safety so I can enforce the size and all that. Plus I'm dealing with these mosto f the time
	class Matrix4 {
	//Private members
	private:
		float* data;

	//Public
	public:
		//Friend Matrix for better conversion between the two
		friend class Matrix;

		//Costructors
		Matrix4(const float* data);
		Matrix4();

		//Copy Constructor
		Matrix4(const Matrix4& copy);

		//Move Constructors
		Matrix4(Matrix4&& move) noexcept;
		Matrix4(Matrix&& move) noexcept;

		//Destructor
		~Matrix4();

		//Getters
		float getData(int index) const;
		float* getDataPointer() const;

		//Setters
		void setData(float data, int index);
		void setData(const float* data);

		//Functions
		void printData() const; //Basically just copied from generic matrix class

		//Operations
		Matrix4& operator=(const Matrix4& other);
		Matrix4& operator=(const Matrix4&& other) noexcept;
		Matrix4 operator+(const Matrix4& other) const;
		Matrix4 operator-(const Matrix4& other) const;
		Matrix4 operator*(float scalar) const;
		Matrix4 operator*(const Matrix4& other) const;
		Vec4 operator*(const Vec4& other) const;

		Matrix4 transpose() const;
		Matrix4 inverse() const;
		float getDeterminant() const;

		//Transformation Matrices (Homogeneous)
		static Matrix4 getScaleMatrix(float xScale, float yScale, float zScale);
		static Matrix4 getTranslationMatrix(float xTranslate, float yTranslate, float zTranslate);
		static Matrix4 getQRotationMatrix(Vec3 axis, float angle);
		static Matrix4 getERotationMatrix(float xRot, float yRot, float zRot);

		//OpenGL Specific Matrices
		//TODO Implement these
		static Matrix4 getModelMatrix(const Vec3& position, const Vec3& rotation, const Vec3& scale);
		static Matrix4 getViewMatrix(const Vec3& cameraRight, const Vec3& cameraUp, const Vec3& cameraFront, const Vec3& cameraPosition);
		static Matrix4 getProjectionMatrix();

	};
}

#endif