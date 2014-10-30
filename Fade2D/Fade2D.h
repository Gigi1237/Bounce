//Define Needed headers
#ifndef FADE2D_EXPORT
#define FADE2D_EXPORT __declspec(dllexport)
#else
#define FADE2D_EXPORT __declspec(dllimport)
#endif

#ifndef Fade2D_TEST
#define Fade2D_TEST


class FADE2D_EXPORT IFade2D {
public:
	virtual bool windowShouldClose() = 0;
	virtual void swapBuffer() = 0;
	virtual void prepareScene() = 0;
	virtual void prepareScene(float R, float G, float B) = 0;
};

class FADE2D_EXPORT IEntity {
public:
	virtual int getVboId() = 0;
	virtual void Draw() = 0;
	virtual void move(float x, float y) = 0;
};

extern "C" FADE2D_EXPORT IFade2D* new_IFade2d(int resX, int resY, char* name);
extern "C" FADE2D_EXPORT IEntity* new_IEntity(float verteces[], int size);

#endif