#pragma once

GLfloat cameraSensitive = 0.7f;
float cameraValueX = 0.f;
float cameraValueY = 0.f;
vec2 delta(0.f,0.f);

bool keys[1024];

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 0.1f;
	if (keys[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;


}

void cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{	
	if (delta == vec2(0.f, 0.f))
	{
		delta == vec2(xpos, ypos);
	}
	cameraValueX = xpos - delta.x;
	cameraValueY = ypos - delta.y;
	
}

void mouseB_callback(GLFWwindow* window, int b, int action, int mods)
{
	if (b == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		isOffset = !isOffset;
	}
}

void resize_callback(GLFWwindow* window, int w, int h) 
{
	glfwSetWindowSize(window, w, w);
	glViewport(0, 0, w, w);
}

void scroll_callback(GLFWwindow* window, double x, double y) 
{
	if (y<=0)
	{
		stretchX += 0.05f;
		stretchY += 0.05f;
	}
	else
	{
		if (stretchX <= 0)
		{
			return;
		}
		stretchX -= 0.05f;
		stretchY -= 0.05f;
	}	
}


void initCallbacks(GLFWwindow* window) 
{	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursorpos_callback);
	glfwSetMouseButtonCallback(window, mouseB_callback);
	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetScrollCallback(window, scroll_callback);
}









