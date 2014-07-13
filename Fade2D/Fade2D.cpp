#include "Fade2D.h"



Fade2D::Fade2D(int resX, int resY, char* name)
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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	const char* vertexShader =
		"#version 400\n"
		"in vec3 vp;"
		"void main () {"
		"	gl_Position = vec4 (vp, 1.0);"
		"}";
	const char* fragmentShader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShader, NULL);
	glCompileShader(fs);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);



}
bool Fade2D::init()
{
	return true;
}

bool Fade2D::windowShouldClose()
{
	return !glfwWindowShouldClose(window);
}

void Fade2D::swapBuffer()
{
	glfwSwapBuffers(window);
}

