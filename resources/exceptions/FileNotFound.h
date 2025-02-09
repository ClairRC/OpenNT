#ifndef FileNotFoundException_h
#define FileNotFoundException_h

#include <exception>

/*
*  This exception is thrown if file can't be opened. Mostly for Shaders.
*/
namespace Resources {
	class FileNotFoundException : public std::exception {

	public:
		const char* what() const noexcept override {
			return "FileNotFoundException: File not found.";
		}
	};
}
#endif
