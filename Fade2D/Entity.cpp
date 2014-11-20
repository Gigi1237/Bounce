#include "internal.h"


///
/// Constructor for the Entity class
///
/// @param xLen Width of entity
/// @param yLen Height of the entity
/// @param xPos Vertical position of the Entity's top left corner
/// @param yPos Horizontal position of the Entity's top left corner
/// @param library Library within which to create the Entity
///
Entity::Entity(float xLen, float yLen, float xPos, float yPos, Fade2D *library){
	pos.x = xPos;
	pos.y = yPos;
	size = glm::vec2(xLen, yLen);
	scaleMatrix = glm::scale(glm::mat4(), glm::vec3(xLen, yLen, 1));
	translationMatrix = glm::translate(glm::mat4(), glm::vec3(pos, 0));
	rotationMatrix = glm::mat4();

	init(library);
}

///
/// Draws the entity at it's current position on the sreen
///
void Entity::draw(){
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix * rotationMatrix * scaleMatrix));
	ShaderHandler::useProgram();
	library->draw();
}

///
/// Moves the entity
///
void  Entity::move(float x, float y){
	pos.x += x;
	pos.y += y;
	translationMatrix = glm::translate(translationMatrix, glm::vec3(x, y, 0));
}

///
/// Rotates the entity
///
void Entity::rotate(float angle)
{
	this->angle += angle;
	rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0.f, 0.f, 1.f));
}

///
/// Get the entity position
///
/// @return Pointer to a C style array with two elements
///
float* Entity::getPosition(){
	return glm::value_ptr(pos);
}


void Entity::init(Fade2D *library){
	ShaderHandler::useProgram();
	matrixLocation = glGetUniformLocation(ShaderHandler::getProgram(), "transform");
	this->library = library;
}