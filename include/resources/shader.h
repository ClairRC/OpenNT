#ifndef shader_h
#define shader_h

#include <string>

/*
* I wrote this when I was still very C-brained and not C++-brained, so this and its
* implementation are bad. I need to rework this all into a shader manager. I don't even
* need this namespace at all now that I think about it.
*/
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