#ifndef shader_h
#define shader_h

#include <string>

#include "../exceptions/resource_exceptions.h"

namespace Resources {
	//Class for shaders
	class Shader {
	private:
		static void getStringFromShaderFile(const char* name, std::string& vertexShader, std::string& fragmentShader);

	public:
		//Constructor
		Shader() = delete; //Do not want to instantiate this

		//Static Functions
		static unsigned int loadShader(const char* name);
	};
}

#endif