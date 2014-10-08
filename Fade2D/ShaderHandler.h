#ifndef SHADERHANDLER
#define SHADERHANDLER

#include <iostream>
#include <fstream>
#include <vector>




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

class ShaderHandler
{
public:
	friend class Entity_INT;
	ShaderHandler();
	~ShaderHandler();
	unsigned int addShader(shaderType type, char* filePath);
	unsigned int addProgram();
	void bindProgram(unsigned int program, unsigned int vertexShader, unsigned int fragmentShader);
	void bindProgram(unsigned int vertexShader, unsigned int fragmentShader);
	unsigned int currentProgram;
protected:
	void useProgram();
private:
	const char * readShader(char* path);
	std::vector<Shader> shaders;
	std::vector<GLuint> programs;
};



#endif