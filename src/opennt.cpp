/*
* This source file holds the main function, it deals with pre-game loop and post-game loop stuff, it handles GLFW and GLAD stuff
* This is mostly just setup stuff.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "opennt.h"

//Initial Screen propties
#define WIDTH 800
#define HEIGHT 600
#define NAME "expreli"

void gameLoop();

int openNT_init() {
	//GLFW Setup
	if (!glfwInit()) {
		std::cout << "GLFW Init Fail" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window setup
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, NAME, NULL, NULL);

	if (window == NULL) {
		std::cout << "Error setting up window" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	//Setup GLAD for OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error setting up GLAD" << std::endl;
		return 1;
	}

	//Viewport
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, 800, 600);

	//Render loop
	//Enable depth test so some faces arent in front of others
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		gameLoop();

		Systems::MovementSystem::processMovement(window);
		Systems::LightingSystem::calculateLighting();
		Systems::RenderSystem::renderEntities();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
