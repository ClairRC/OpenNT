#ifndef VectorIncorrectDimensionsException_h
#define VectorIncorrectDimensionsException_h

#include <exception>

/*
* This exception is thrown if the user tries to do some vector operation, and one or both vectors have dimensions
* that are undefined for that operation. Includes things like addition requiring both vectors to be the same size
*/
namespace Math {
	class VectorIncorrectDimensionsException : public std::exception {

	public:
		const char* what() const noexcept override {
			return "VectorIncorrectDimensionsException: Verctor dimensions undefined for this operation";
		}
	};
}
#endif
