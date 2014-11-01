#include "internal.h"

Entity::Entity(float xLen, float yLen, float xPos, float yPos, Fade2D *library){
	pos.x = xPos;
	pos.y = yPos;
	modelMatrix = glm::scale(glm::mat4(), glm::vec3(xLen, yLen, 1));
	transformMatrix = glm::translate(glm::mat4(), glm::vec3(pos, 0));

	init(library);
}

void Entity::Draw(){
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
	ShaderHandler::useProgram();
	library->draw();

}

void  Entity::move(float x, float y){
	pos.x += x;
	pos.y += y;
	transformMatrix = glm::translate(glm::mat4(), glm::vec3(pos, 0));
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
}

float* Entity::getPosition(){
	return glm::value_ptr(pos);
}


void Entity::init(Fade2D *library){
	ShaderHandler::useProgram();
	matrixLocation = glGetUniformLocation(ShaderHandler::getProgram(), "transform");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix * modelMatrix));
	this->library = library;
}