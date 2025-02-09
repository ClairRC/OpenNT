/*
* This source file holds the main function, it deals with pre-game loop and post-game loop stuff, it handles GLFW and GLAD stuff
* This is mostly just setup stuff.
*/

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#include "math_stuff/math_stuff.h"
#include "resources/resources.h"

//Initial Screen propties
#define WIDTH 800
#define HEIGHT 600
#define NAME "expreli"

//Testing stuff. DELETE THIS!! :D
using namespace std;
using namespace Math;
using namespace Resources;
//int temp();

int main() {
	//GLFW Setup
	if (!glfwInit()) {
		cout << "GLFW Init Fail" << endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window setup
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, NAME, NULL, NULL);

	if (window == NULL) {
		cout << "Error setting up window" << endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	//Setup GLAD for OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Error setting up GLAD" << endl;
		return 1;
	}

	//Viewport
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, 800, 600);

	//Render loop
	//Enable depth test so some faces arent in front of others
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);

	const float vertices[] = {
		//Position				Color

		//Front face
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f, //top-left
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 1.0f, //top-right
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 1.0f, //bottom-right
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f, 1.0f, //bottom-left

		//back face
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f, 1.0f, //top-left
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f, 1.0f, //top-right
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 0.0f, 1.0f, //bottom-right
		-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 1.0f//bottom-left
	};


	int indices[36] = { 
	0, 1, 2, //Front face
	2, 3, 0,

	4, 0, 3, //Left face 
	3, 7, 4,

	5, 4, 7, //Back face
	7, 6, 5,

	1, 5, 6, //Right face
	6, 2, 1,

	4, 5, 1, //Top face
	1, 0, 4,

	3, 2, 6, //Bottom face
	6, 7, 3 };

	int attributeSizes[2] = { 3, 4 };

	float vertices2[] = {
	 0.5f,  0.5f, 0.0f,  0.5, 0, 0, 0.5,// top right
	 0.5f, -0.5f, 0.0f,  0.5, 0, 0, 0.5,// bottom right
	-0.5f, -0.5f, 0.0f,  0.5, 0, 0, 0.5,// bottom left
	-0.5f,  0.5f, 0.0f,   0.5, 0, 0, 0.5// top left 
	};
	int indices2[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	int attribuetSizes2[2] = { 3, 4 };

	unsigned int shader = Shader::loadShader("basic");
	unsigned int VAO = Resources::VAO::createVAO(vertices, attributeSizes, indices, sizeof(vertices), sizeof(attributeSizes), sizeof(indices));
	unsigned int planeVAO = Resources::VAO::createVAO(vertices2, attribuetSizes2, indices2, sizeof(vertices2), sizeof(attribuetSizes2), sizeof(indices2));

	float identity[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	Vec3 triangleLocation(0, 0, 0);
	Vec3 camPosition(0, 0, 0);

	Vec3 camUp = Vec3(0, 1, 0);
	Vec3 camFront = Vec3(0, 0, -1);
	Vec3 camRight = Vec3(1, 0, 0);
	Vec3 plane(0, 0, 0);

	Matrix4 model(Matrix4::getModelMatrix(triangleLocation, Vec3(0, 0, 0), Vec3(2, 1, 1)));
	//Matrix4 model(identity);
	Matrix4 view(Matrix4::getViewMatrix(camUp, camRight, camFront, camPosition));
	//Matrix4 view(identity);
	Matrix4 projection(Matrix4::getProjectionMatrix());
	//Matrix4 projection(identity);

	model.printData();

	//unsigned int modelMat = glGetUniformLocation(shader, "model");
	//unsigned int viewMat = glGetUniformLocation(shader, "view");
	//unsigned int projectionMat = glGetUniformLocation(shader, "projection");

	/*Matrix4 test(projection * view * model);
	model.printData();
	std::cout << std::endl;
	view.printData();
	std::cout << std::endl;
	projection.printData();
	std::cout << std::endl;
	test.printData();
	std::cout << std::endl;
	Vec4 c1 = test * Vec4(-0.5f, -0.5f, 0, 1);
	Vec4 c2 = test * Vec4(0.5f, -0.5f, 0, 1);
	Vec4 c3 = test * Vec4(0.5f, 0.5f, 0, 1);

	std::cout << "Expected coords: " << c1.x() << " " << c1.y() << " " << c1.z() << " " << c1.w() << endl
		<< c2.x() << " " << c2.y() << " " << c2.z() << " " << c2.w() << endl
		<< c3.x() << " " << c3.y() << " " << c3.z() << " " << c3.w() << endl;

	std::cout << modelMat << endl << viewMat << endl << projectionMat << endl;*/

	
	int testMat = glGetUniformLocation(shader, "trans");

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

		//triangleLocation.setZ(std::sin(glfwGetTime())*5);
		//model = Matrix4::getModelMatrix(triangleLocation, Vec3(0, 0, 0), Vec3(1, 1, 1));
		//camPosition.setZ(std::sin(glfwGetTime())*5);
		//view = Matrix4::getViewMatrix(camUp, camRight, camFront, camPosition);

		//glUniformMatrix4fv(modelMat, 1, GL_FALSE, model.getDataPointer());
		//glUniformMatrix4fv(viewMat, 1, GL_FALSE, view.getDataPointer());
		//glUniformMatrix4fv(projectionMat, 1, GL_FALSE, projection.getDataPointer());
		
		//camPosition.setZ(std::sin(glfwGetTime()) * 10);
		//camPosition.setY(std::cos(glfwGetTime()) * 10);

		//camPosition.setZ(std::sin(glfwGetTime()) * 10);
		//camPosition.setY(std::cos(glfwGetTime()) * 10);

		camPosition.setZ((std::sin(glfwGetTime()) * 10)-10);
		camPosition.setY(std::cos(glfwGetTime()) * 10);

		camFront = (Vec3(0,0,-10) - camPosition).normalize();
		camUp = (camRight.cross(camFront)).normalize();
		//camRight = (camFront.cross(camUp)).normalize();

		triangleLocation.setX((std::sin(glfwGetTime()) * 5));
		triangleLocation.setZ((std::cos(glfwGetTime()) * 5)-10);
		Matrix4 test = Matrix4(
			Matrix4::getModelMatrix(triangleLocation, Vec3(-glfwGetTime(), glfwGetTime(), 0), Vec3(1, 1, 1))*
			Matrix4::getViewMatrix(camRight, camUp, camFront, camPosition) *
			Matrix4::getProjectionMatrix());
		glUniformMatrix4fv(testMat, 1, GL_FALSE, test.getDataPointer());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		triangleLocation.setX((std::cos(glfwGetTime()) * 5));
		triangleLocation.setZ((std::sin(glfwGetTime()) * 5)-10);
		test = Matrix4(
			Matrix4::getModelMatrix(triangleLocation, Vec3(glfwGetTime(), -glfwGetTime(), 0), Vec3(1, 1, 1)) *
			Matrix4::getViewMatrix(camRight, camUp, camFront, camPosition) *
			Matrix4::getProjectionMatrix());
		glUniformMatrix4fv(testMat, 1, GL_FALSE, test.getDataPointer());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindVertexArray(planeVAO);

		test = Matrix4(
			Matrix4::getModelMatrix(Vec3(0, 0, -10), Vec3(1.57, 0, 0), Vec3(10, 10, 10)) *
			Matrix4::getViewMatrix(camRight, camUp, camFront, camPosition) *
			Matrix4::getProjectionMatrix());
		glUniformMatrix4fv(testMat, 1, GL_FALSE, test.getDataPointer());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

//Everything below is for testing purposes. 
//This is just for testing
/*int main() {
	temp();
	Resources::Shader::loadShader("basic");

	return 0;
}

//Just sets up my shit so I can use it in my testing main function
int temp() {
	//GLFW Setup
	if (!glfwInit()) {
		cout << "GLFW Init Fail" << endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window setup
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, NAME, NULL, NULL);

	if (window == NULL) {
		cout << "Error setting up window" << endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	//Setup GLAD for OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Error setting up GLAD" << endl;
		return 1;
	}

	//Viewport
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, 800, 600);

	return 0;
}
*/