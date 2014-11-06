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
	modelMatrix = glm::scale(glm::mat4(), glm::vec3(xLen, yLen, 1));
	transformMatrix = glm::translate(glm::mat4(), glm::vec3(pos, 0));

	init(library);
}

///
/// Draws the entity at it's current position on the sreen
///
void Entity::Draw(){
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
	ShaderHandler::useProgram();
	library->draw();

}

///
/// Moves the entity
///
void  Entity::move(float x, float y){
	pos.x += x;
	pos.y += y;
	transformMatrix = glm::translate(glm::mat4(), glm::vec3(pos, 0));
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
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
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
	this->library = library;
}