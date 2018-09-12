#pragma once


class Shader
{
private:
	const GLchar* VertexShader;
	const GLchar* FragmentShader;

	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	void InitShaders();
	void InitProgram();
	void LoadShaders(std::string& path);
	
public:
	Shader(const GLchar* name);
	void Active();
	GLuint Sprogram();
	~Shader();
};

inline Shader::Shader(const GLchar * name)
{
	std::string path = "Shaders/" + (std::string)name;
	LoadShaders(path);	
}

void Shader::InitShaders()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShader, nullptr);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char info[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		std::cout << info;
		glfwTerminate();
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShader, nullptr);
	glCompileShader(fragmentShader);

	GLint status2;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);
	if (status2 == GL_FALSE)
	{
		char info[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		std::cout << info;
		glfwTerminate();
	}
}

void Shader::InitProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint status3;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status3);
	if (status3 == GL_FALSE)
	{
		char log[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << log;
		glfwTerminate();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	delete[] VertexShader;
	delete[] FragmentShader;
}

inline void Shader::LoadShaders(std::string & path)
{
	std::string resv, resf;
	resv = path + "V.lshader";
	resf = path + "F.lshader";
	{
		ifstream str(resv, ios::in|ios::binary|ios::ate);
		ifstream::pos_type size = str.tellg();
		GLint fSize = (GLint)str.tellg();
		GLchar* memblock;
		memblock = new char[1 + fSize];
		str.seekg(0, ios::beg);
		str.read(memblock, size);
		str.close();
		memblock[size] = '\0';		

		VertexShader = memblock;
		str.close();		
	}	
	{
		ifstream str(resf, ios::in | ios::binary | ios::ate);
		ifstream::pos_type size = str.tellg();
		GLint fSize = (GLint)str.tellg();
		GLchar* memblock;
		memblock = new char[1 + fSize];
		str.seekg(0, ios::beg);
		str.read(memblock, size);
		str.close();
		memblock[size] = '\0';

		FragmentShader = memblock;
		str.close();	
	}	
	InitShaders();
	InitProgram();

}


void Shader::Active() 
{
	glUseProgram(shaderProgram);
}

inline GLuint Shader::Sprogram()
{
	return shaderProgram;
}

inline Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}