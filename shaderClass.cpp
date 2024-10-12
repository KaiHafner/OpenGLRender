#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{
	string vertexCode = get_file_contents(vertexFile);
	string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Creates vertex shader and gets its reference
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //Attached vertex source to the vertex shader object
	glCompileShader(vertexShader); //Compiles the vertex shader into machine code

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Creates fragment shader and gets its reference
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); //Attached shader source to the fragment shader object
	glCompileShader(fragmentShader); //Compiles the fragment shader into machine code

	ID = glCreateProgram(); //Creates shader program and gets its reference
	glAttachShader(ID, vertexShader); //Attaches the Vertex to the Shader Program
	glAttachShader(ID, fragmentShader); //Attaches the Fragment Shader to the Shader Program
	glLinkProgram(ID); //Links all the shaders together into shader Program

	compileErrors(ID, "PROGRAM");

	//Deletes the now useless vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() 
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type) 
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}