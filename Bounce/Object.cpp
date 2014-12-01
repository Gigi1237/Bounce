#include "Object.h"


Object::Object(IEntity* baseEntity)
{
	entity = baseEntity;
}


Object::~Object()
{
}

void Object::draw()
{
	entity->draw();
}
void Object::move(float x, float y)
{
	entity->move(x, y);
}
void Object::setPos(float x, float y)
{
	entity->setPos(x, y);
}
void Object::rotate(float angle)
{
	entity->rotate(angle);
}
void Object::setAngle(float angle)
{
	entity->setAngle(angle);
}
float* Object::getPosition()
{
	return entity->getPosition();
}
