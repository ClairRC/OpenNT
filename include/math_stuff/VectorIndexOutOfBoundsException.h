#ifndef VectorIndexOutOfBoundsException_h
#define VectorIndexOutOfBoundsException_h

#include <exception>

/*
* This exception is thrown if the user tries to access in index of the vector data that is outside of the bounds
* of the vector.
*/
namespace Math {
	class VectorIndexOutOfBoundsException : std::exception {

	public:
		const char* what() const noexcept override {
			return "VectorIndexOutOfBoundsException: Index is outside of vector size";
		}
	};
}

#endif