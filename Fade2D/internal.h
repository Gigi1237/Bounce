//Define Needed headers

#ifndef Fade2D_INT
#define Fade2D_INT

#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderHandler.h"
#include "Fade2D.h"


///
/// Class that handles most graphics operations
///
class Fade2D : public IFade2D {
public:
	Fade2D(int resX, int resY, char* name);
	bool windowShouldClose();
	void swapBuffer();
	void prepareScene();
	void prepareScene(float R, float G, float B);
	GLFWwindow* window;
private:
	GLuint vs;
	GLuint fs;
};

///
/// Class that represents an entity
///
class Entity : public IEntity {
public:
	Entity(GLfloat verteces[], int size);
	int getVboId();
	void Draw();
	void move(float x, float y);
private:
	GLuint vbo_id;
	GLuint vao_id;
	glm::mat4 matrix;
	int matrixLocation;
};

#endif