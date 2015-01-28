#ifndef Fade2D_TEST
#define Fade2D_TEST

//Define Needed headers
#ifdef WIN32
#ifndef FADE2D_EXPORT
#define FADE2D_EXPORT __declspec(dllexport)
#else
#define FADE2D_EXPORT __declspec(dllimport)
#endif
#else
#define FADE2D_EXPORT
#endif
class IEntity;

#include <string>

enum letters
{
    a = 65,
    b = 66,
    c = 67,
    d = 68,
    e = 69,
    f = 70,
    g = 71,
    h = 72,
    i = 73,
    j = 74,
    k = 75,
    l = 76,
    m = 77,
    n = 78,
    o = 79,
    p = 80,
    q = 81,
    r = 82,
    s = 83,
    t = 84,
    u = 85,
    v = 86,
    w = 87,
    x = 88,
    y = 89,
    z = 90,
    up = 265,
    down = 264,
    left = 263,
    right = 262,
    space = 32,
    backspace = 259
};

FADE2D_EXPORT typedef void(*keyHandler)(int);

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
    virtual void setKeyPressHandler(letters letter, keyHandler handler) = 0;
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

FADE2D_EXPORT IFade2D* new_IFade2d(int resX, int resY, const char* name);

#endif
