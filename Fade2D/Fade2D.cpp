#include "internal.h"

Fade2D_INT *lib;

Fade2D_INT::Fade2D_INT(int resX, int resY, char* name)
{
	lib = this;
	//Start GL context and open windows
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(resX, resY, name, NULL, NULL);
	//this->maxEntity = new int[maxEntity];
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	shaderHandler = *new ShaderHandler();
	shaderHandler.currentProgram = shaderHandler.addProgram();
	shaderHandler.bindProgram(shaderHandler.addShader(vertex, "..\\Fade2D\\vertexShader.txt"), shaderHandler.addShader(fragment, "..\\Fade2D\\fragmentShader.txt"));
}

bool Fade2D_INT::windowShouldClose()
{
	glfwPollEvents();
	return !glfwWindowShouldClose(window);
}

void Fade2D_INT::swapBuffer()
{
	glfwSwapBuffers(window);
}

void Fade2D_INT::prepareScene()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Fade2D_INT::prepareScene(float R, float G, float B)
{
	glClearColor(R, G, B, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

unsigned int Fade2D_INT::getProgramId()
{
	return shaderHandler.currentProgram;
}

Entity* new_entity(float verteces[], int size)
{
	return new Entity_INT(verteces, size, lib);
}
Fade2D* new_fade2d(int resX, int resY, char* name)
{
	return new Fade2D_INT(resX, resY, name);
}


