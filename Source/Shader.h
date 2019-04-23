#pragma once

class Shader
{
private:

	enum class Type
	{
		nullShader = -1,
		Vertex = 0,
		Geometry = 1,
		Fragment = 2
	} type;

	struct ShaderSources
	{
		string Vertex;
		string Geometry;
		string Fragment;

	} shaderSources;

	stringstream ss[3];

	bool isGeometry = false;

	GLuint shaderProgram;

	void InitProgram();
	void LoadShaders(std::string& path);
	GLuint CompileShader(GLuint type, string& source);


public:
	Shader(const GLchar* name);
	void Active();
	GLuint Sprogram();
	~Shader();
};


inline Shader::Shader(const GLchar * name)
{
	std::string path = "Data/Shaders/" + (std::string)name;
	LoadShaders(path);	
}


inline GLuint Shader::CompileShader(GLuint type, string & source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char info[512];
		glGetShaderInfoLog(id, 512, NULL, info);
		std::cout << "Shader Error\n" << info;
		glfwTerminate();
	}
	return id;
}

void Shader::InitProgram()
{
	GLuint vs, gs, fs;

	vs = CompileShader(GL_VERTEX_SHADER, shaderSources.Vertex);
	if(isGeometry) gs = CompileShader(GL_GEOMETRY_SHADER, shaderSources.Geometry);
	fs = CompileShader(GL_FRAGMENT_SHADER, shaderSources.Fragment);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	if (isGeometry)
	{
		glAttachShader(shaderProgram, gs);
	}
	glLinkProgram(shaderProgram);

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		char log[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout<<"Shader Program Error!!\n"<< log;
		glfwTerminate();
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	if (isGeometry)
	{
		glDeleteShader(gs);
	}
	for (size_t i = 0; i < 3; i++)
	{
		ss[i].clear();
	}
	
}

void Shader::LoadShaders(std::string & path)
{
	string sPath = path + ".shader";
	type = Type::nullShader;
	ifstream stream(sPath.c_str());

	string line;
	while (getline(stream,line)) 
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = Type::Vertex;
				continue;
			}
			if (line.find("geometry") != string::npos)
			{
				type = Type::Geometry;
				isGeometry = true;
				continue;
			}
			if (line.find("fragment") != string::npos)
			{
				type = Type::Fragment;
				continue;
			}
		}
		if (type != Type::nullShader)
		{
			ss[(int)type] << line <<endl;
		}
	}
	stream.close();



	shaderSources = {
		ss[(int)Type::Vertex].str(), 
		ss[(int)Type::Geometry].str(), 
		ss[(int)Type::Fragment].str()};
	
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