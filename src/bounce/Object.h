#pragma once

#include <Fade2D.h>
#include "Bounce.h"
#include "World.h"
#include "vec2.h"

class World;


struct BoundingBox
{
	BoundingBox();
	BoundingBox(vec2 center, vec2 size, float angle)
	{
		vec2 halfSize = size / 2;
		topLeft = vec2(center.x - halfSize.x, center.y - halfSize.y);
		topRight = vec2(center.x + halfSize.x, center.y - halfSize.y);
		bottomLeft = vec2(center.x - halfSize.x, center.y + halfSize.y);
		bottomRight = vec2(center.x + halfSize.x, center.y + halfSize.y);

		topLeft.RotateAroundPoint(angle, center);
		topRight.RotateAroundPoint(angle, center);
		bottomLeft.RotateAroundPoint(angle, center);
		bottomRight.RotateAroundPoint(angle, center);

		this->center = center;
		this->size = size;
	}
	vec2 topLeft;
	vec2 topRight;
	vec2 bottomLeft;
	vec2 bottomRight;
	vec2 center;
	vec2 size;
};

struct BoundingCircle
{
	BoundingCircle();
	BoundingCircle(vec2 center, float radius) : center(center), radius(radius) {}
	vec2 center;
	float radius;
};

class Object
{
public:
	Object(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle = 0.f);
	~Object();
	void draw();
	BoundingBox boundingBox;
protected:
	IEntity* entity;
	bool locked;
	vec2 position;
	vec2 size;
	float angle;
};

class PlayerObject : public Object
{
public:
	PlayerObject(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle = 0.f);
	void move(vec2 mov);
	void moveTo(vec2 pos);
	void update(vec2 accel, double timeStep, std::vector<Object> worldObjects);
	BoundingCircle boundingCircle;
private:
	float radius;
	vec2 speed;
	vec2 desiredPos;
};

class Background : public Object
{
public:
	Background(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle = 0.f);
};

vec2 checkCollision(BoundingBox boundingBox, BoundingCircle boundingCircle);
