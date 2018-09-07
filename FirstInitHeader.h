#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>


using namespace std;
using namespace glm;



GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat currentTime = 0.0f;
mat4 viewMatrix;