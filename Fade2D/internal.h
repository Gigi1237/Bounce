//Define Needed headers

#ifndef FADE2D
#define FADE2D

#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderHandler.h"
#include "Fade2D.h"



class Fade2D_INT : public Fade2D {
public:
	friend class Entity_INT;
	Fade2D_INT(int resX, int resY, char* name);
	bool windowShouldClose();
	void swapBuffer();
	unsigned int getProgramId();
	void prepareScene();
	void prepareScene(float R, float G, float B);

	GLFWwindow* window;
private:
	ShaderHandler shaderHandler;
	GLuint vs;
	GLuint fs;
};

class Entity_INT : public Entity {
public:
	Entity_INT(GLfloat verteces[], int size, Fade2D_INT* lib);
	int getVboId();
	void Draw();
	void move(float x, float y);
private:
	GLuint vbo_id;
	GLuint vao_id;
	Fade2D_INT* lib;
	glm::mat4 matrix;
	int matrixLocation;
};

#endif