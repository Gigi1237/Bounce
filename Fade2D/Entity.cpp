#include "Fade2D.h"



Entity::Entity(){
	glGenBuffers(1, &id);
};
Entity::Entity(GLfloat verteces[], int size){
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, verteces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
};

int Entity::getId(){
	return id;
}

void Entity::Draw(Fade2D lib)
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(lib.program);
	glBindVertexArray(lib.vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glfwPollEvents();
}