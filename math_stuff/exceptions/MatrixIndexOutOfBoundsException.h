#ifndef MatrixIndexOutOfBoundsException_h
#define MatrixIndexOutOfBoundsException_h

#include <exception>

/*
* This exception is thrown if the user tries to access in index of the matrix data that is outside of the bounds 
* of the matrix. This isn't strictly necessary because the Matrix class uses a vector to store the data, however, 
* for the sake of making sure there is no unexpected behavior, I am adding this.
*/
namespace Math {
	class MatrixIndexOutOfBoundsException : std::exception {
	
	public:
		const char* what() const noexcept override {
			return "MatrixIndexOutOfBoundsException: Index is outside of matrix size";
		}
	};
}

#endif