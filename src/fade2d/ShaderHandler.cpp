#include "internal.h"

/// Group of functions dedicated to handling of shaders
namespace ShaderHandler {

	static const char* readShader(const char* path);
	static std::vector<Shader> shaders;
	static std::vector<GLuint> programs;
	static unsigned int currentProgram;


	///
	/// Adds shader to the shader vector.
	///
	/// @param type shaderType enum which represents the type of the shader
	/// @param filePath Filepath of the shader
	///
	/// @return ID of the shader
	unsigned int addShader(shaderType type, const char* filePath)
	{
		//Adds a new shader to the vector and returns it's id
		shaders.push_back(*(new Shader(type, readShader(filePath))));
		return shaders.capacity() - 1;
	}

	///
	/// Adds program to the program vector and sets itself as the current program.
	///
	/// @return ID of the program
	///
	unsigned int addProgram()
	{
		//Adds a new program to the Programs Vertex and returns it's id
		GLuint i = glCreateProgram();
		programs.push_back(i);
		currentProgram = programs.size() - 1;
		return programs.size() - 1;
	}

	///
	/// Attaches shaders to the current program and links it
	///
	/// @param vertexShader ID of the vertex shader
	/// @param fragmentShader ID of the fragment shader
	///
	void bindProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		//Attaches vertex and fragment shaders to program
		glAttachShader(programs[currentProgram], shaders[vertexShader].id);
		glAttachShader(programs[currentProgram], shaders[fragmentShader].id);
		//Links the program
		glLinkProgram(programs[currentProgram]);
	}

	///
	/// Attaches shaders to a program and links it.
	///
	/// @param program Program ID
	/// @param vertexShader ID of the vertex shader
	/// @param fragmentShader ID of the fragment shader
	///
	void bindProgram(unsigned int program, unsigned int vertexShader, unsigned int fragmentShader)
	{
		//Attaches vertex and fragment shaders to program
		glAttachShader(programs[program], shaders[vertexShader].id);
		glAttachShader(programs[program], shaders[fragmentShader].id);
		//Links the program
		glLinkProgram(programs[program]);
	}

	///
	/// Sets program that is in use to the current program
	/// 
	void useProgram(){
		glUseProgram(programs[currentProgram]);
	}
	///
	/// Sets program that is in use
	///
	/// @param program Program ID
	///
	void useProgram(unsigned int program){
		glUseProgram(programs[program]);
	}


	///
	/// Gets current program
	///
	unsigned int getProgram()
	{
		return programs[currentProgram];
	}

	///
	/// Gets a program
	///
	/// @param program Program ID
	///
	unsigned int getProgram(unsigned int program)
	{
		return programs[program];
	}

	Shader::Shader(shaderType type, const char* shader)
	{
		//Creates a new shader binds it to it's source and compiles it
		id = glCreateShader(type);
		glShaderSource(id, 1, &shader, NULL);
		glCompileShader(id);

		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		GLchar* log = (GLchar*)malloc(length);

		glGetShaderInfoLog(id, 200, &length, log);

		if (length>1){
		        printf("Log file: ");
			printf("%s\n", log);
		}

	}


	// Private functions which reads shader from file
	const char * readShader(const char* path)
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
}
