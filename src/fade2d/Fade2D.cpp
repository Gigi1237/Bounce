#include "internal.h"

///
/// Constructor for Fade2D
///
/// @param resX Diagonal resolution of the desired window
/// @param resY Vertical resolution of the desired window
/// @param name Name of the desired window
///
Fade2D::Fade2D(int resX, int resY, const char* name){
	//Start GL context and open windows
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 16);

	window = glfwCreateWindow(resX, resY, name, NULL, NULL);
	if(window == NULL) {
  	  std::cerr << "Failed to open GLFW window. Are your drivers up-to-date ?" << std::endl;
  	  glfwTerminate();

  	  exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	if(!glfwGetCurrentContext()) {
   	 std::cerr << "Couldn't create OpenGL context" << std::endl;
   	 exit(EXIT_FAILURE);
	}

    addClassKeyHandler(this);


	glewExperimental = GL_TRUE;
	//glewInit();

        GLenum err = glewInit();
        if (err != GLEW_OK)
          std::cout << "ERROR 1: " << glewGetErrorString(err);
          //exit(1); // or handle the error in a nicer way
        if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
          std::cout << "ERROR 2: " << glewGetErrorString(err);
          //exit(1); // or handle the error in a nicer way

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	//std::cout << std::endl << "GLError: " << gluErrorString(glGetError()) << std::endl;

	ShaderHandler::addProgram();
	ShaderHandler::bindProgram(ShaderHandler::addShader(ShaderHandler::vertex, SHADERPATH"vertexShader.txt"), ShaderHandler::addShader(ShaderHandler::fragment, SHADERPATH"fragmentShader.txt"));
	ShaderHandler::useProgram();

	glUniformMatrix4fv(
		glGetUniformLocation(ShaderHandler::getProgram(), "proj"),
		1,
		GL_FALSE,
		glm::value_ptr(glm::ortho(0.f, (float)resX, (float)resY, 0.f, 1.f, -1.f)));

	this->genBaseObject();

	this->resX = resX;
	this->resY = resY;
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
void Fade2D::swapBuffer(){
	glfwSwapBuffers(window);
}

///
/// Prepares the scene for rendering using default color
///
void Fade2D::prepareScene(){
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

///
/// Prepares scene for rendering using a custom color
///
void Fade2D::prepareScene(float R, float G, float B){
	glClearColor(R, G, B, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/// Interface for creating an object of IEntity
///
/// @param xLen Lenght of the Entity
/// @param yLen Height of the Entity
/// @param xPos Horizontal position of the Entity
/// @param yPos Vertical position of the Entiy
///
IEntity* Fade2D::newEntity(float xLen, float yLen, float xPos, float yPos, std::string texturePath, float angle){
	return new Entity(xLen, yLen, xPos, yPos, texturePath, this, angle);
}

void Fade2D::draw(){

	glBindVertexArray(base_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Fade2D::genBaseObject(){
	glGenBuffers(1, &base_vbo);
	glGenVertexArrays(1, &base_vao);
	glBindVertexArray(base_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, base_vbo);
	//GLfloat verteces[] = {
	//	0.f, 1.f, 0.f,
	//	0.f, 0.f, 0.f,
	//	1.f, 1.f, 0.f,
	//	1.f, 0.f, 0.f
	//};

	GLfloat verteces[] = {
		-0.5f, 0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		0.5f, 0.5f, 0.f,
		0.5f, -0.5f, 0.f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

int* Fade2D::getWindowSize()
{
	static int res[] = { resX, resY };
	return res;
}

void Fade2D::setKeyPressHandler(letters letter, keyHandler handler)
{
    keyHandlers.push_back(keyHandlerFunc(letter, handler));
}

void Fade2D::classKeyHandler(int keyPressed, int action)
{
    for (auto& funcsAndKeus : keyHandlers)
    {
        if (keyPressed == funcsAndKeus.key)
            funcsAndKeus.func(action);
    }
}

/// Interface for creating a Fade2D object
///
/// @param resX Horizontal resolution
/// @param resY Vertical resolution
/// @param name Name of the window
///
IFade2D* new_IFade2d(int resX, int resY, const char* name){
	return new Fade2D(resX, resY, name);
}
