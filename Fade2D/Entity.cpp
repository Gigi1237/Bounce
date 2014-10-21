#include "internal.h"




Entity_INT::Entity_INT(GLfloat verteces[], int size, Fade2D_INT* lib){
	this->lib = lib;
	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	matrixLocation = glGetUniformLocation(lib->shaderHandler.getProgram(), "matrix");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
};

int Entity_INT::getVboId()
{
	return vbo_id;
}

void Entity_INT::Draw()
{

	lib->shaderHandler.useProgram();
	glBindVertexArray(vao_id);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void  Entity_INT::move(float x, float y)
{
	matrix = new float[]{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, 0.0f, 1.0f
	};
}