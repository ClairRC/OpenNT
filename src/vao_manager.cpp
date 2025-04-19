#include "resource_manager/vao_manager.h"

#include <glad/glad.h>

namespace ResourceManager {
	VAOManager* VAOManager::instance = nullptr;
	unsigned int VAOManager::commonVAO = -1;

	VAOManager::VAOManager() {}

	VAOManager::~VAOManager() {
		if (instance != nullptr)
			delete instance;
	}

	VAOManager* VAOManager::getVAOManager() {
		if (instance == nullptr)
			instance = new VAOManager();

		return instance;
	}


	//There are a number of hardcoded values because this engine is
	//going for a specific art style that uses no 3D models, 
	//so the VAO management is less complicated. I DO want to expand it, but for now, I'll do this.
	
	//Sets up VAO if it doesn't already have a value
	//Returns -1 if there is an error
	unsigned int VAOManager::getVAO() {
		//If the VAO exists, return it. Otherwise, set it up
		if (this->commonVAO != -1)
			return this->commonVAO;

		//Square vertices for textured quads
		float vertices[] = {
			0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f // top left 
		};

		int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		unsigned int VBO;
		unsigned int EBO;

		glGenVertexArrays(1, &this->commonVAO); //Create VAO
		glBindVertexArray(this->commonVAO); //Bind VAO

		glGenBuffers(1, &VBO); //Create VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//Bind VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copy data to VBO

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Create first attribute (position)
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float))); //Create second attribute (texture coords)

		//Enable attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &EBO); //Create EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Copy data to buffer

		glBindVertexArray(0); //Unbind VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind EBO

		//Return VAO
		return this->commonVAO;
	}
}