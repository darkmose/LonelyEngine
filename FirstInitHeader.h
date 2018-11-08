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

#include "Time.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Primitive.h"
#include "Callbacks.h"
#include "Input.h"
#include "RenderTexture.h"
#include "Sprite.h"

GLuint glCreateUnifBuffer(GLsizeiptr size, GLuint idBind)
{
	GLuint ubo;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW); 
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, idBind, ubo);
	
	return ubo;
}

void glSetUnifVariable(GLuint unifBlockId, GLsizeiptr offset, GLsizeiptr size, void* var) 
{
	glBindBuffer(GL_UNIFORM_BUFFER, unifBlockId);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, var);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
