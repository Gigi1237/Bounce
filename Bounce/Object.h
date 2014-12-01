#ifndef OBJECT_H
#define OBJECT_H

#include "..\Fade2D\Fade2D.h"

class Object
{
public:
	Object(IEntity* baseEntity);
	~Object();
	void draw();
	void move(float x, float y);
	void setPos(float x, float y);
	void rotate(float angle);
	void setAngle(float angle);
	float* getPosition();
private:
	IEntity* entity;
};

#endif