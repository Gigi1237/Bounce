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
private:
	
	GLuint vs;
	GLuint fs;
};

class FADE2D_EXPORT Entity {
public:
	Entity(GLfloat verteces[], int size, Fade2D lib);
	int getVboId();
	void Draw(Fade2D lib);
private:
	GLuint vbo_id;
	GLuint vao_id;
};

#endif