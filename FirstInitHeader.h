#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};
struct Texture
{
	string type;
	GLuint id;
	aiString name;
};

#include "Application.h"
#include "Time.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Primitive.h"
#include "Callbacks.h"
#include "Input.h"
#include "RenderTexture.h"
#include "Sprite.h"

GLuint glUniformBuffer(GLsizeiptr size, GLuint idBind)
{
	GLuint ubo;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW); 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, idBind, ubo);
	
	return ubo;
}

template<class T>
void glUniformData(GLuint unifBlockId, GLsizeiptr size, GLsizeiptr offset, T var)
{
	glBindBuffer(GL_UNIFORM_BUFFER, unifBlockId);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, &var);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void glUniformDataObject(GLuint unifBlockId, GLsizeiptr size, GLsizeiptr offset, void* var)
{
	glBindBuffer(GL_UNIFORM_BUFFER, unifBlockId);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, var);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint U_Global_LightsPDS;

void glUniformLights()
{
	glDeleteBuffers(1, &U_Global_LightsPDS);
	U_Global_LightsPDS = glUniformBuffer(48*Light::pointLs.size() + 36*Light::dirLs.size() + 60*Light::spotLs.size(), 3);
}

void ActiveLights()
{
	int pSize, dSize, sSize;
	pSize = Light::pointLs.size();
	dSize = Light::dirLs.size();
	sSize = Light::spotLs.size();


	for (size_t i = 0; i < pSize; i++)
	{
		glUniformDataObject(U_Global_LightsPDS, 16, (48 * i)+0, &Light::pointLs[i]->position);
		glUniformDataObject(U_Global_LightsPDS, 16, (48 * i)+16, &Light::pointLs[i]->color);
		glUniformDataObject(U_Global_LightsPDS, 4, (48 * i)+32, &Light::pointLs[i]->strengh);
		glUniformDataObject(U_Global_LightsPDS, 4, (48 * i)+36, &Light::pointLs[i]->Kc);
		glUniformDataObject(U_Global_LightsPDS, 4, (48 * i)+40, &Light::pointLs[i]->Kl);
		glUniformDataObject(U_Global_LightsPDS, 4, (48 * i)+44, &Light::pointLs[i]->Kq);
	}
	for (size_t i = 0; i < dSize; i++)
	{
		size_t _offset = 36 * i + 48*pSize;
	    glUniformDataObject(U_Global_LightsPDS, 16, _offset+0, &Light::dirLs[i]->direction);
	    glUniformDataObject(U_Global_LightsPDS, 16, _offset+16, &Light::dirLs[i]->color);
	    glUniformDataObject(U_Global_LightsPDS, 4,  _offset+32, &Light::dirLs[i]->strengh);
	}
	for (size_t i = 0; i < sSize; i++)
	{
		size_t _offset = 48 * i + 48*pSize + 32*dSize;
		glUniformDataObject(U_Global_LightsPDS, 48, _offset, Light::spotLs[i]);
	}
}
