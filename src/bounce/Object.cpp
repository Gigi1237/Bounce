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
			speed = speed - (collisionVec * dotProduct(speed, collisionVec)) * 1.85f;
            break;
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
		boundingCircle = BoundingCircle(position, size.x / 2);
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

		if (t < 0 || t > 1)
		{
			// intersection point is not actually within line segment
            return false;
		}
		return true;
	}
	else if (dist < circle.radius)
	{
		// two possible intersection points
		float dt = sqrt(circle.radius * circle.radius - dist * dist) / sqrt(dl);

		// intersection point nearest to A
		float t1 = t - dt;
        int i = 0;
		vec2 i1X(A.x + t1 * d.x, A.y + t1 * d.y);
		if (t1 < 0 || t1 > 1)
		{
			// intersection point is not actually within line segment
            i++;
		}

		// intersection point farthest from A
		float t2 = t + dt;
		vec2 i2(A.x + t2 * d.x, A.y + t2 * d.y);
		if (t2 < 0 || t2 > 1)
		{
			// intersection point is not actually within line segment
			//return false;
            i++;
		}
        if (i < 2)
            return true;
        else
            return false;
	}
	else
	{
		// no intersection
		return false;
	}
}

vec2 checkCollision(BoundingBox boundingBox, BoundingCircle boundingCircle)
{
    int collision = 0;
	std::vector<vec2> normal;
	if (lineCircleCollision(boundingBox.topLeft, boundingBox.topRight, boundingCircle)){
		normal.push_back(boundingBox.topRight - boundingBox.topLeft);
        collision++;
	}
	if (lineCircleCollision(boundingBox.bottomLeft, boundingBox.bottomRight, boundingCircle)){
        normal.push_back(boundingBox.bottomRight - boundingBox.bottomLeft);
        collision++;
	}
	if (lineCircleCollision(boundingBox.topLeft, boundingBox.bottomLeft, boundingCircle)){
        normal.push_back(boundingBox.bottomLeft - boundingBox.topLeft);
        collision++;
	}
	if (lineCircleCollision(boundingBox.topRight, boundingBox.bottomRight, boundingCircle)){
        normal.push_back(boundingBox.bottomRight - boundingBox.topRight);
        collision++;
	}

	if (collision == 1){
		float len = normal[0].Length();
		normal[0].Normalize();
		float a = normal[0].x;
		normal[0].x = normal[0].y;
		normal[0].y = -a;
		return normal[0];
	}
    else if (collision == 2){
        //vec2 norm = normal[0] - normal[1];
        //norm.Normalize();
        //return norm;
        float dist[4];
        dist[0] = distance(boundingBox.topRight, boundingCircle.center);
        dist[1] = distance(boundingBox.topLeft, boundingCircle.center);
        dist[2] = distance(boundingBox.bottomRight, boundingCircle.center);
        dist[3] = distance(boundingBox.bottomLeft, boundingCircle.center);
        float minDist = 5000;
        int index;
        for (int i = 0; i < 4; i++)
        {
            if (dist[i] < minDist){
                minDist = dist[i];
                index = i;
            }
        }
        vec2 normVec;
        switch (index)
        {
        case 0:
            normVec = boundingBox.topRight;
            break;
        case 1:
            normVec = boundingBox.topLeft;
            break;
        case 2:
            normVec = boundingBox.bottomRight;
            break;
        case 3:
            normVec = boundingBox.bottomLeft;
            break;
        }
        normVec -= boundingBox.center;
        return normVec.Normalize();
    }
	else
		return vec2(0.0f, 0.0f);

}

