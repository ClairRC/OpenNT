#include <glad/glad.h>

#include "../header_files/vao.h"

namespace Resources {
	//Creates and returns VAO id
	//TODO: 
	//Once I get mesh/model objects, they should probably create the VBO and EBO themselves
	//This depends though I'm not really sure yet. So far this should be fine? I just want the arguments to be a lil easier.
	//On the other hand, this generates, binds, sets, and stores VBO and EBO in one go, so it's TECHNICALLY more efficient I think?
	//Also maybe better error handling for mismatching sizes.
	//Honestly I dunno make this more readable in general.
	unsigned int VAO::createVAO
		(const float* vertices,
		const int* verticesAttributeSizes,
		const int* indices,
		const size_t verticesSize,
		const size_t verticesAttributeSizesSize,
		const size_t indicesSize) {

		//Create IDs for each buffer
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		//Num attributes (gotten from array size)
		const int numAttributes = verticesAttributeSizesSize / sizeof(int);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//Set up VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		//Set up EBO if one has been set
		if (indices != nullptr && indicesSize >= 3) {
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
		}

		//Get stride value
		int stride = 0;
		for (int i = 0; i < numAttributes; ++i) {
			stride += verticesAttributeSizes[i];
		}
		
		stride *= sizeof(float);

		//Get attribute pointers
		size_t offset = 0;
		for (int i = 0; i < numAttributes; ++i) {
			glVertexAttribPointer(i, verticesAttributeSizes[i], GL_FLOAT, GL_FALSE, stride, (void*)offset);
			glEnableVertexAttribArray(i);

			offset += verticesAttributeSizes[i] * sizeof(float);
		}

		//FINALLY unbind buffres and return VAO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return VAO;
	}
}