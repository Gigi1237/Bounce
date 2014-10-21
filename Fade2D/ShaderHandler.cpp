#include "internal.h"


ShaderHandler::ShaderHandler()
{
	currentProgram = 0;
}


ShaderHandler::~ShaderHandler()
{
}

unsigned int ShaderHandler::addShader(shaderType type, char* filePath)
{
	//Adds a new shader to the vector and returns it's id
	shaders.push_back(*(new Shader(type, readShader(filePath))));
	return shaders.capacity() - 1;
}

const char * ShaderHandler::readShader(char* path)
{
	// Reads the shader into a string
	std::ifstream shader;
	shader.open(path, std::ios::in);
	std::string contents((std::istreambuf_iterator<char>(shader)),
		std::istreambuf_iterator<char>());
	shader.close();

	//Creates a new string from contents since returning contents will result in a Null pointer after it's deletion
	char* ptr = new char[contents.length() + 1];
	std::strcpy(ptr, contents.c_str());
//#ifdef _DEBUG
//	std::cout << std::endl << ptr;
//#endif
	return ptr;
}

unsigned int ShaderHandler::addProgram()
{
	//Adds a new program to the Programs Vertex and returns it's id
	GLuint i = glCreateProgram();
	std::cout << i;
	programs.push_back(i);
	return programs.size() - 1;
}

void ShaderHandler::bindProgram(unsigned int program, unsigned int vertexShader, unsigned int fragmentShader)
{
	//Attaches vertex and fragment shaders to program
	glAttachShader(programs[program], shaders[vertexShader].id);
	glAttachShader(programs[program], shaders[fragmentShader].id);
	//Links the program
	glLinkProgram(programs[program]);
}

void ShaderHandler::bindProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	//Attaches vertex and fragment shaders to program
	glAttachShader(programs[currentProgram], shaders[vertexShader].id);
	glAttachShader(programs[currentProgram], shaders[fragmentShader].id);
	//Links the program
	glLinkProgram(programs[currentProgram]);
}

void ShaderHandler::useProgram()
{
	glUseProgram(programs[currentProgram]);
}

unsigned int ShaderHandler::getProgram()
{
	return programs[currentProgram];
}

unsigned int ShaderHandler::getProgram(unsigned int program)
{
	return programs[program];
}

Shader::Shader(shaderType type, const char* shader)
{
	//Creates a new shader binds it to it's source and compiles it
	std::cout << shader;
	id = glCreateShader(type);
	glShaderSource(id, 1, &shader, NULL);
	glCompileShader(id); 
}