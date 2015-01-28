//Define Needed headers

#ifndef Fade2D_INT
#define Fade2D_INT

#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include "basic.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Fade2D.h"
#include "ShaderHandler.h"
#include "InputHandler.h"
#include "Texture.h"
#include "shaderpath.h"

struct keyHandlerFunc {
    keyHandlerFunc(int key, keyHandler func) : key(key), func(func) { }
    int key;
    keyHandler func;
};

///
/// Class that handles most graphics operations
///
class Fade2D : public IFade2D {
public:
	friend class Entity;
	Fade2D(int resX, int resY, const char* name);
	bool windowShouldClose();
	void swapBuffer();
	void prepareScene();
	void prepareScene(float R, float G, float B);
	int* getWindowSize();
    void setKeyPressHandler(letters letter, keyHandler handler);
	IEntity *newEntity(float xLen, float yLen, float xPos, float yPos, std::string texturePath, float angle = 0);
    void classKeyHandler(int keyPressed, int action);
	GLFWwindow* window;
private:
	void draw();
	void genBaseObject();
	GLuint base_vbo;
	GLuint base_vao;
	int resX;
	int resY;
    std::vector<keyHandlerFunc> keyHandlers;
    void KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
};

///
/// Class that represents an entity
///
class Entity : public IEntity {
public:
	Entity(float xLen, float yLen, float xPos, float yPos, std::string texturePath, Fade2D *libray, float angle = 0);
    ~Entity();
	void draw();
	void move(float x, float y);
	void setPos(float x, float y);
	void rotate(float angle);
	void setAngle(float angle);
	float* getPosition();
	float* getSize() { return glm::value_ptr(size); }
	float getAngle() { return angle; }
private:
	void init(Fade2D *library);
	Fade2D *library;
	Texture *texture;
	glm::vec2 pos;
	glm::vec2 size;
	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	int matrixLocation;
	float angle;
};

#endif
