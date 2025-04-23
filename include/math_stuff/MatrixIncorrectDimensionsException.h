#ifndef MatrixIncorrectDimensionsException_h
#define MatrixIncorrectDimensionsException_h

#include <exception>

/*
* This exception is thrown if the user tries to do some matrix operation, and one or both matrices have dimensions
* that are undefined for that operation. Includes things like addition requiring both matrices to be the same size,
* determinant requiring matrix to be square, multiplcation requiring the first matrices columns to equal the second's rows, etc.
*/

namespace Math {
	class MatrixIncorrectDimensionsException : public std::exception {
	
	public:
		const char* what() const noexcept override {
			return "MatrixIncorrectDimensionsException: Matrix dimensions undefined for this operation";
		}
	};
}
#endif
