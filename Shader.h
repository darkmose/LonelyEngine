#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SOIL/SOIL.h>

const GLchar* shaderS = "#version 330 core \n"
"\n"
"layout (location = 0) in vec3 pos; \n"
"//layout (location = 1) in vec3 color;\n"
"layout (location = 1) in vec2 textPos;\n"

"//out vec3 Color;\n"
"out vec2 TexturePos;\n"
"uniform vec2 stretch;\n"
"uniform vec2 offset;\n"

"uniform mat4 transform;\n"

"void main(){\n"
"//Color = color;\n"
"TexturePos = vec2(textPos.x * stretch.x + offset.x ,1-(textPos.y * stretch.y + offset.y));\n"
"gl_Position = transform * vec4(pos.x,pos.y,pos.z,1.0);\n"
"}\n";

const GLchar* shaderF = "#version 330 core"
"\n"
"//in vec3 Color;\n"
"in vec2 TexturePos;\n"

"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"

"out vec4 color;\n"
"void main(){\n"
"	color = mix(texture(texture1,TexturePos),texture(texture2,vec2(TexturePos.x, TexturePos.y)),0.4f);\n"
"}";


GLuint shaderProgram;
GLuint vertexShader;
GLuint fragmentShader;

void initShaders() 
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderS, nullptr);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char info[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		std::cout << info;
		delete(info);
		
	}


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderF, nullptr);
	glCompileShader(fragmentShader);

	GLint status2;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);
	if (status2 == GL_FALSE)
	{
		char info[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		std::cout << info;
		delete(info);
	}
}

void initProgramShader() 
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
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


float stretchX = 1;
float stretchY = 1;
float offsetX = 0;
float offsetY = 0;

bool isOffset = false;

void shaderUniforms()
{
	glUniform2f(glGetUniformLocation(shaderProgram, "stretch"), stretchX, stretchY);
	if (isOffset)
	{
		glUniform2f(glGetUniformLocation(shaderProgram, "offset"), offsetX, offsetY);
	}		
}