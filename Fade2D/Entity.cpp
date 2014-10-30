#include "internal.h"

Entity::Entity(GLfloat verteces[], int size){
	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	matrix = glm::mat4();

	ShaderHandler::useProgram();
	matrixLocation = glGetUniformLocation(ShaderHandler::getProgram(), "transform");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
};

int Entity::getVboId()
{
	return vbo_id;
}

void Entity::Draw()
{
	ShaderHandler::useProgram();
	glBindVertexArray(vao_id);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void  Entity::move(float x, float y)
{
	//matrix[3][0] += x;
	//matrix[3][1] += y;

	matrix = glm::translate(matrix, glm::vec3(x, y, 0));
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}