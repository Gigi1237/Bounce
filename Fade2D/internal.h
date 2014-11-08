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
	friend class Entity;
	Fade2D(int resX, int resY, char* name);
	bool windowShouldClose();
	void swapBuffer();
	void prepareScene();
	void prepareScene(float R, float G, float B);
	IEntity *newEntity(float xLen, float yLen, float xPos, float yPos);
	GLFWwindow* window;
private:
	void draw();
	void genBaseObject();
	GLuint base_vbo;
	GLuint base_vao;
};

///
/// Class that represents an entity
///
class Entity : public IEntity {
public:
	Entity(float xLen, float yLen, float xPos, float yPos, Fade2D *libray);
	int getVboId();
	void Draw();
	void move(float x, float y);
	float* getPosition();
private:
	void init(Fade2D *library);
	Fade2D *library;
	glm::vec2 pos;
	glm::mat4 modelMatrix;
	glm::mat4 transformMatrix;
	int matrixLocation;
};

#endif