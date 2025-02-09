#ifndef vec4_h
#define vec4_h

namespace Math {
	class Vec4 {
		//Private members
	private:
		float xVal;
		float yVal;
		float zVal;
		float wVal;

		//Public stuff
	public:
		//Constructors
		Vec4(float x, float y, float z, float w);
		Vec4();

		//Getters
		float x() const;
		float y() const;
		float z() const;
		float w() const;

		//Setters
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);

		//Operations
		Vec4 operator+ (const Vec4& other) const;
		Vec4 operator- (const Vec4& other) const;
		Vec4 operator* (float scalar) const;
		Vec4 normalize() const;
		float dot(const Vec4& other) const;
	};
}
#endif