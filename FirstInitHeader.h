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
#include "Callbacks.h"
#include "Input.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Primitive.h"


