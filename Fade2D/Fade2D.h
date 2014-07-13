//Define Needed headers
#ifndef FADE2D_EXPORT
#define FADE2D_EXPORT __declspec(dllexport)
#else
#define FADE2D_EXPORT __declspec(dllimport)
#endif

#ifndef FADE2D
#define FADE2D

#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>


class FADE2D_EXPORT Fade2D {
public:
	Fade2D(int resX, int resY, char* name);
	bool init(); 
	bool windowShouldClose();
	void swapBuffer();
	GLFWwindow* window;
	GLuint program;
	GLuint vao;
private:
	
	GLuint vs;
	GLuint fs;

	//int* maxEntity;
};

class FADE2D_EXPORT Entity {
public:
	Entity();
	Entity(GLfloat verteces[], int size);
	int getId();
	void Draw(Fade2D lib);
private:
	GLuint id;
};

#endif