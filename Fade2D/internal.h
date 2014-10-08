//Define Needed headers

#ifndef FADE2D
#define FADE2D

#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Fade2D.h"
#include <iostream>


class Fade2D_INT : public Fade2D {
public:
	Fade2D_INT(int resX, int resY, char* name);
	bool init();
	bool windowShouldClose();
	void swapBuffer();
	unsigned int getProgramId();
	GLFWwindow* window;
	GLuint program;
private:

	GLuint vs;
	GLuint fs;
};

class Entity_INT : public Entity {
public:
	Entity_INT(GLfloat verteces[], int size);
	int getVboId();
	void Draw(unsigned int program);
private:
	GLuint vbo_id;
	GLuint vao_id;
};

//extern "C" __declspec(dllexport) IKlass* __cdecl create_klass()
//{
//	return new MyKlass;
//}

#endif