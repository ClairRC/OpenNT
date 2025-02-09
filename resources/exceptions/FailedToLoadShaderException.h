#ifndef FailedToLoadShaderException_h
#define FailedToLoadShaderException_h

#include <exception>

/*
*  This exception is thrown if file can't be opened. Mostly for Shaders.
*/
namespace Resources {
	class FailedToLoadShaderException : public std::exception {

	public:
		const char* what() const noexcept override {
			return "FailedToLoadShaderException: Failed to load shader.";
		}
	};
}
#endif
