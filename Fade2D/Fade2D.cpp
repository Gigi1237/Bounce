#include "internal.h"

Fade2D_INT *lib;

Fade2D_INT::Fade2D_INT(int resX, int resY, char* name)
{
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

	ShaderHandler::addProgram();
	ShaderHandler::bindProgram(ShaderHandler::addShader(ShaderHandler::vertex, "..\\Fade2D\\vertexShader.txt"), ShaderHandler::addShader(ShaderHandler::fragment, "..\\Fade2D\\fragmentShader.txt"));
}

bool Fade2D_INT::windowShouldClose()
{
	return !glfwWindowShouldClose(window);
}

void Fade2D_INT::swapBuffer()
{
	glfwSwapBuffers(window);
}


Fade2D* new_fade2d(int resX, int resY, char* name)
{
	return new Fade2D_INT(resX, resY, name);
}

Entity* new_entity(float verteces[], int size)

{
	return new Entity_INT(verteces, size);
}
