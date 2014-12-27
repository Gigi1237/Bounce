#ifndef Fade2D_TEST
#define Fade2D_TEST

//Define Needed headers
#ifndef FADE2D_EXPORT
#define FADE2D_EXPORT __declspec(dllexport)
#else
#define FADE2D_EXPORT __declspec(dllimport)
#endif

class IEntity;

#include <string>

///
/// Interface for the Fade2D class
///
class FADE2D_EXPORT IFade2D {
public:
	virtual bool windowShouldClose() = 0;
	virtual void swapBuffer() = 0;
	virtual void prepareScene() = 0;
	virtual void prepareScene(float R, float G, float B) = 0;
	virtual int* getWindowSize() = 0;
	virtual IEntity *newEntity(float xLen, float yLen, float xPos, float yPos, std::string texturePath, float angle = 0) = 0;
};

///
/// Interface for the entity class
///
class FADE2D_EXPORT IEntity {
public:
	virtual void draw() = 0;
	virtual void move(float x, float y) = 0;
	virtual void setPos(float x, float y) = 0;
	virtual void rotate(float angle) = 0;
	virtual void setAngle(float angle) = 0;
	virtual float* getPosition() = 0;
	virtual float* getSize() = 0;
	virtual float getAngle() = 0;
};

FADE2D_EXPORT IFade2D* new_IFade2d(int resX, int resY, char* name);

#endif