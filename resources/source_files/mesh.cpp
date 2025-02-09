#include <glad/glad.h>

#include "../header_files/mesh.h"

namespace Resources {
	//Constructor
	Mesh::Mesh(float* vertices, int* verticesAttributeSizes, int* indices,
		size_t verticesSize, size_t verticesAttributeSizesSize, size_t indicesSize)
		: vertices(vertices), verticesAttributeSizes(verticesAttributeSizes), indices(indices),
		verticesSize(verticesSize), verticesAttributeSizesSize(verticesAttributeSizesSize), indicesSize(indicesSize) 
	{
		this->VAO = VAO::createVAO(vertices, verticesAttributeSizes, indices, verticesSize,
			verticesAttributeSizesSize, indicesSize);
	}

	//Destructor
	Mesh::~Mesh() {
		delete[] this->vertices;
		delete[] this->verticesAttributeSizes;
		delete[] this->indices;
	}
}