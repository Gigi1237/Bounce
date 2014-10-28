#include "internal.h"




Entity_INT::Entity_INT(GLfloat verteces[], int size){
	glGenBuffers(1, &vbo_id);
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, size, verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
};

int Entity_INT::getVboId(){
	return vbo_id;
}

void Entity_INT::Draw()
{
	ShaderHandler::useProgram();
	glBindVertexArray(vao_id);
	//glClearColor(0.5, 0.5, 0.5, 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glfwPollEvents();
}