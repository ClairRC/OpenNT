#ifndef vec_h
#define vec_h

#include <iostream>

namespace Math {
	//Forward Declaration
	class Matrix;

	class Vec {

	//Private fields
	private:
		//I was considering using smart pointers, but since I'm mostly using this for OpenGL, 
		//I think raw pointer are nicer. Plus I want to create a deep copy which is so annoying with smart pointers.
		size_t size;
		float* data;

		//Public stuff
	public:
		//Constructors
		Vec(size_t size);
		Vec(size_t size, const float* data);
		
		//Copy Constructor
		Vec(const Vec& copy);

		//Move Constructor
		Vec(Vec&& move) noexcept;

		//Destructor
		~Vec();

		//Getters
		float getData(int index) const;
		size_t getSize() const;

		//Setters
		void setData(const float* data);
		void setData(float data, int index);

		//Operations
		Vec& operator= (const Vec& other);
		Vec& operator= (const Vec&& other) noexcept;
		Vec operator+ (const Vec& other) const;
		Vec operator- (const Vec& other) const;
		Vec operator* (float scalar) const;
		float dot(Vec& other) const;
		Vec normalize() const;
		float getMagnitude() const;
		Matrix toColumnMatrix() const;
		Matrix toRowMatrix() const;
	};
}
#endif