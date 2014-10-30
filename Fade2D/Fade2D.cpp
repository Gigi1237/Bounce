#include "internal.h"

///
/// Constructor for Fade2D
///
/// @param resX Diagonal resolution of the desired window
/// @param resY Vertical resolution of the desired window
/// @param name Name of the desired window
///
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
	std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;

	ShaderHandler::addProgram();
	std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;
	ShaderHandler::bindProgram(ShaderHandler::addShader(ShaderHandler::vertex, "..\\Fade2D\\vertexShader.txt"), ShaderHandler::addShader(ShaderHandler::fragment, "..\\Fade2D\\fragmentShader.txt"));
	std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;
	ShaderHandler::useProgram();
	std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;

	float x = 0.f;
	float y = 0.f;

	glm::mat4 Projection = glm::ortho(0.f, 800.0f, 600.0f, 0.f, 10.0f, -10.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 5), // Camera is at (0,0,5), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	std::cout << std::endl << "X= " << (MVP * glm::vec4(x, y, 0.f, 0.f))[0] << " Y= " << (MVP * glm::vec4(x, y, 0.f, 0.f))[0];
	glm::vec4 b = glm::vec4(x, y, 0.f, 0.f) * MVP;


	glUniformMatrix4fv(glGetUniformLocation(ShaderHandler::getProgram(), "proj"), 1, GL_FALSE, glm::value_ptr(glm::ortho(0.f, 800.0f, 600.0f, 0.f, 10.0f, -10.0f)));
	std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;

}

///
/// Checks if the window should close
///
bool Fade2D::windowShouldClose()
{
	glfwPollEvents();
	return !glfwWindowShouldClose(window);
}

///
/// Swaps back and front buffers, must be done every scene after rendering
///
void Fade2D::swapBuffer()
{
	glfwSwapBuffers(window);
}

///
/// Prepares the scene for rendering using default color
///
void Fade2D::prepareScene()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

///
/// Prepares scene for rendering using a custom color
///
void Fade2D::prepareScene(float R, float G, float B)
{
	glClearColor(R, G, B, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/// Interface for creating an object of Entity
IEntity* new_IEntity(float verteces[], int size)
{
	return new Entity(verteces, size);
}

/// Interface for creating an object of Fade2D
IFade2D* new_IFade2d(int resX, int resY, char* name)
{
	return new Fade2D(resX, resY, name);
}


