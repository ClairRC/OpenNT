#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "opennt.h"

//Initial Screen propties
#define WIDTH 800
#define HEIGHT 600
#define NAME "expreli"
/*
* I was REALLY not sure what to do here.
* I forward declared a gameLoop function to abstract the render loop I have at the bottom, but 
* this means that you must include a void gameLoop() in main that gets called every frame.
* I don't think there is really anything wrong with that, but that's what I did. Other than that,
* this class sets up the initial things that you need, and holds the render loop which updates
* logic or rendering or whatever else each frame.
*
* TODO: Better customizability, probably better error handling, things like that.
*/

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
