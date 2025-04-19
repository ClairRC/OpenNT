#include "resources/shader.h"

#include <iostream>
#include <fstream>
#include <glad/glad.h>

#include "resources/resource_exceptions.h"

namespace Resources {
	//Loads the shader. Not yet sure where I'm going to store this....
	unsigned int Shader::loadShader(const char* name) {
		//Get both strings.
		std::string vertexShader;
		std::string fragmentShader;
		getStringFromShaderFile(name, vertexShader, fragmentShader);

		//Compile vertex shader
		unsigned int vert;
		const char* vsource = vertexShader.c_str();
		vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &vsource, NULL);
		glCompileShader(vert);

		//Compile fragment shader
		unsigned int frag;
		const char* fsource = fragmentShader.c_str();
		frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &fsource, NULL);
		glCompileShader(frag);

		//Link them
		unsigned int prog;
		prog = glCreateProgram();

		glAttachShader(prog, vert);
		glAttachShader(prog, frag);
		glLinkProgram(prog);

		//Delete intermediate shader objects
		glDeleteShader(vert);
		glDeleteShader(frag);

		//Check for success
		int success;
		glGetProgramiv(prog, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(prog, 512, NULL, infoLog);
			
			std::cerr << infoLog << std::endl;
			throw FailedToLoadShaderException();
		}

		//Returning program id for now. i maaay or may not end up addign this to a map
		//so I can keep track of what is/not loaded and organize it.
		return prog;
	}

	//Helper function that takes name and references to the strings and gives them the shaders.
	void Shader::getStringFromShaderFile(const char* name, std::string& vertexShader, std::string& fragmentShader) {
		//Set up strings
		std::string temp;
		std::string shaderPath("../shaders/");

		std::ifstream in;

		//Write to vertexShader string
		in.open(shaderPath + name + ".vert");

		//Check if file is open and write to string
		if (!in.is_open()) {
			throw FileNotFoundException();
		}

		while (std::getline(in, temp)) {
			vertexShader += temp + "\n";
		}

		in.close();

		//Repeat for fragment shader
		in.open(shaderPath + name + ".frag");

		if (!in.is_open()) {
			throw FileNotFoundException();
		}

		while (std::getline(in, temp)) {
			fragmentShader += temp + "\n";
		}

		in.close();
	}
}