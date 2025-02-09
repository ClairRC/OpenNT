#ifndef mesh_h
#define mesh_h

#include <iostream>
#include <vector>

#include "../../math_stuff/math_stuff.h"
#include "../header_files/vao.h"

namespace Resources {

	//Mesh object. Holds the information for each mesh.
	class Mesh {

	//All my functions and stuff are going to stay private because I ONLY want the model class to handle these. 
	private:
		//Make model a friend class so it can use these functions
		friend class Model;

		//Private members
		unsigned int VAO;

		float* vertices;
		int* verticesAttributeSizes;
		int* indices;

		size_t verticesSize;
		size_t verticesAttributeSizesSize;
		size_t indicesSize;

		//Constructors. I'm making these private because these should only be accessed from my model class
		Mesh(float* vertices, int* verticesAttributeSizes, int* indices,
			size_t verticesSize, size_t verticesAttributeSizesSize, size_t indicesSize);

		//Not allowing copying/moving
		Mesh(const Mesh& copy) = delete;
		Mesh(Mesh&& move) noexcept = delete;

		//Destructor
		~Mesh();

		//Draw function
		void draw(const unsigned int shader) const;
	};
}

#endif 