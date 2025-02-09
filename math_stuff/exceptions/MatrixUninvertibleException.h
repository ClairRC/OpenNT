#ifndef MatrixUninvertibleException_h
#define MatrixUninvertibleException_h

#include <exception>

/*
* This exception is thrown if the Matrix::inverse() command finds the matrix is uninvertible.
*/
namespace Math {
	class MatrixUninvertibleException : std::exception {

	public:
		const char* what() const noexcept override {
			return "MatrixUninvertibleException: Matrix is uninvertible";
		}
	};
}

#endif