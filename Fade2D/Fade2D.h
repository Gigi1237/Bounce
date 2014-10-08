//Define Needed headers
#ifndef FADE2D_EXPORT
#define FADE2D_EXPORT __declspec(dllexport)
#else
#define FADE2D_EXPORT __declspec(dllimport)
#endif

#ifndef FADE2D_INT
#define FADE2D_INT

#define GLEW_STATIC


class FADE2D_EXPORT Fade2D {
public:
	virtual bool init() = 0;
	virtual bool windowShouldClose() = 0;
	virtual void swapBuffer() = 0;
	virtual unsigned int getProgramId() = 0;
};

class FADE2D_EXPORT Entity {
public:
	virtual int getVboId() = 0;
	virtual void Draw() = 0;
};

extern "C" FADE2D_EXPORT Fade2D* new_fade2d(int resX, int resY, char* name);
extern "C" FADE2D_EXPORT Entity* new_entity(float verteces[], int size);

#endif