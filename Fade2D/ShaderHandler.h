#ifndef SHADERHANDLER
#define SHADERHANDLER

#include <iostream>
#include <fstream>
#include <vector>


namespace ShaderHandler {

enum shaderType{
	vertex = GL_VERTEX_SHADER,
	fragment = GL_FRAGMENT_SHADER
};

class Shader
{
public:
	Shader(shaderType, const char* shader);
	unsigned int id;
private:
	shaderType type;
};

unsigned int addShader(shaderType type, char* filePath);
unsigned int addProgram();
void bindProgram(unsigned int program, unsigned int vertexShader, unsigned int fragmentShader);
void bindProgram(unsigned int vertexShader, unsigned int fragmentShader);
void useProgram();

}

#endif