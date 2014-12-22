#include "Object.h"


Object::Object(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle) : boundingBox(Pos, Len, angle)
{
	entity = lib->newEntity(Len.x, Len.y, Pos.x, Pos.y, texturePath, angle);
	position = Pos;
	size = Len;
	this->angle = angle;
}

Object::~Object()
{
}

void Object::draw()
{
	entity->draw();
}

PlayerObject::PlayerObject(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle) : Object(lib, Len, Pos, texturePath, angle), desiredPos(Pos), boundingCircle(Pos, Len.x / 2), speed(0.f, 0.f)
{
	radius = Len.x / 2;
}

void PlayerObject::move(vec2 mov)
{
	desiredPos += mov;
}

void PlayerObject::moveTo(vec2 pos)
{
	desiredPos = pos;
}

void PlayerObject::update(vec2 accel, double timeStep, std::vector<Object> worldObjects)
{
	speed += accel * (float)timeStep;
	desiredPos += speed;
	boundingCircle.center = desiredPos;
	bool collide = false;
	for (auto &object : worldObjects)
	{
		vec2 collisionVec = checkCollision(object.boundingBox, boundingCircle);
		if (collisionVec != vec2(0.f, 0.f)){
			collide = true;
			speed = speed - (collisionVec * dotProduct(speed, collisionVec)) * 2;
		}
	}
	if (!collide){
		position = desiredPos;
		entity->setPos(desiredPos.x, desiredPos.y);
	}
	else{
		desiredPos = position;
		boundingCircle.center = position;
	}

	if (!isOnScreen(vec2(1280, 720), boundingCircle.center))
	{
		vec2 a(600, 75);
		entity->setPos(a.x, a.y);
		position = a;
		desiredPos = position;
		boundingCircle = *new BoundingCircle(position, size.x / 2);
		speed = vec2(0, 0);
	}
}

Background::Background(IFade2D* lib, vec2 Len, vec2 Pos, std::string texturePath, float angle) : Object(lib, Len, Pos, texturePath, angle)
{
	boundingBox = BoundingBox(vec2(0.f, 0.f), vec2(0.f, 0.f), 0.f);
}

bool lineCircleCollision(vec2 A, vec2 B, BoundingCircle circle)
{
	vec2 d = B - A;
	if ((d.x == 0) && (d.y == 0))
	{
		// A and B are the same points, no way to calculate intersection
		return false;
	}

	float dl = (d.x * d.x + d.y * d.y);
	float t = ((circle.center.x - A.x) * d.x + (circle.center.y - A.y) * d.y) / dl;

	// point on a line nearest to circle center
	vec2 nearest(A.x + t * d.x, A.y + t * d.y);

	float dist = distance(nearest, circle.center);

	if (dist == circle.radius)
	{
		// line segment touches circle; one intersection point
		vec2 i = nearest;

		//if (t < 0 || t > 1)
		//{
		//	// intersection point is not actually within line segment
		//	return
		//}
		return false;
	}
	else if (dist < circle.radius)
	{
		// two possible intersection points

		double dt = sqrt(circle.radius * circle.radius - dist * dist) / sqrt(dl);

		// intersection point nearest to A
		double t1 = t - dt;
		vec2 i1X(A.x + (float)t1 * d.x, A.y + (float)t1 * d.y);
		if (t1 < 0 || t1 > 1)
		{
			// intersection point is not actually within line segment
			return false;
		}

		// intersection point farthest from A
		double t2 = t + dt;
		vec2 i2(A.x + (float)t2 * d.x, A.y + (float)t2 * d.y);
		if (t2 < 0 || t2 > 1)
		{
			// intersection point is not actually within line segment
			return false;
		}
		return true;
	}
	else
	{
		// no intersection
		return false;
	}
}

vec2 checkCollision(BoundingBox boundingBox, BoundingCircle boundingCircle)
{
	bool collision = false;
	vec2 normal;
	if (lineCircleCollision(boundingBox.topLeft, boundingBox.topRight, boundingCircle)){
		normal = boundingBox.topRight - boundingBox.topLeft;
		collision = true;
	}
	else if (lineCircleCollision(boundingBox.bottomLeft, boundingBox.bottomRight, boundingCircle)){
		normal = boundingBox.bottomRight - boundingBox.bottomLeft;
		collision = true;
	}
	else if (lineCircleCollision(boundingBox.topLeft, boundingBox.bottomLeft, boundingCircle)){
		normal = boundingBox.bottomLeft - boundingBox.topLeft;
		collision = true;
	}
	else if (lineCircleCollision(boundingBox.topRight, boundingBox.bottomRight, boundingCircle)){
		normal = boundingBox.bottomRight - boundingBox.topRight;
		collision = true;
	}

	if (collision){
		float len = normal.Length();
		normal.Normalize();
		float a = normal.x;
		normal.x = normal.y;
		normal.y = -a;
		return normal;
	}
	else
		return vec2(0.0f, 0.0f);

}

