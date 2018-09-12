#pragma once
#include "Light.h"

static class Callbacks 
{	
private:
	static GLfloat lastX, lastY;
	static GLFWwindow* window;
	static vec2 deltaMouse;
	static bool keys[400];
	static bool mods[10];
	static float speed;
	static GLfloat cameraSpeed;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouseB_callback(GLFWwindow* window, int b, int action, int mods);
	static void resize_callback(GLFWwindow* window, int w, int h);
	static void scroll_callback(GLFWwindow* window, double x, double y);
public:

	Callbacks(GLFWwindow* window);
	static void do_movement(Light*);
	static void initCallbacks();
};


inline Callbacks::Callbacks(GLFWwindow * _window)
{
	window = _window;
}

GLfloat Callbacks::lastX;
GLfloat Callbacks::lastY;
GLFWwindow* Callbacks::window;
vec2 Callbacks::deltaMouse;
bool Callbacks::keys[400];
GLfloat Callbacks::cameraSpeed;
bool Callbacks::mods[10];
float Callbacks::speed = 1.f;


void Callbacks::do_movement(Light* lPos)
{
	cameraSpeed = Time::deltaTime * 5* speed;
	

	if (keys[GLFW_KEY_W])
		Camera::mainCamera->transform.TranslatePos(Camera::mainCamera->Forward(cameraSpeed));
	if (keys[GLFW_KEY_S])
		Camera::mainCamera->transform.TranslatePos(Camera::mainCamera->Forward(-cameraSpeed));
	if (keys[GLFW_KEY_A])
		Camera::mainCamera->transform.TranslatePos(Camera::mainCamera->Right(-cameraSpeed));
	if (keys[GLFW_KEY_D])
		Camera::mainCamera->transform.TranslatePos(Camera::mainCamera->Right(cameraSpeed));
	if (keys[GLFW_KEY_ESCAPE])
		glfwTerminate();
	if (keys[340])
		speed = 2.f;
	else speed = 1.f;
	if (keys[GLFW_KEY_SPACE])
		Camera::mainCamera->transform.TranslatePos(vec3(0, 4 * Time::deltaTime, 0));
	if (keys[GLFW_KEY_F])
		Camera::mainCamera->transform.TranslatePos(vec3(0, -4 * Time::deltaTime, 0));
	if (keys[GLFW_KEY_UP])
		lPos->SetLPos(vec3(0, 0, Time::deltaTime *10));
	if (keys[GLFW_KEY_DOWN])
		lPos->SetLPos(vec3(0, 0, -Time::deltaTime * 10));
	if (keys[GLFW_KEY_LEFT])
		lPos->SetLPos(vec3(Time::deltaTime * 10, 0, 0));
	if (keys[GLFW_KEY_RIGHT])
		lPos->SetLPos(vec3(-Time::deltaTime * 10, 0, 0));
	if (keys[GLFW_KEY_I])
		lPos->SetLPos(vec3(0, Time::deltaTime * 10, 0));
	if (keys[GLFW_KEY_K])
		lPos->SetLPos(vec3(0, -Time::deltaTime * 10, 0));

}

void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) 
	{
		keys[key] = true;		
	}
	else if (action == GLFW_RELEASE) 
	{
		keys[key] = false;		
	}	

}

void Callbacks::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{		
	deltaMouse = vec2((xpos - lastX), (lastY - ypos));
	Camera::mainCamera->Look(deltaMouse.y, deltaMouse.x);
	lastX = xpos;
	lastY = ypos;
}

void Callbacks::mouseB_callback(GLFWwindow* window, int b, int action, int mods)
{
	if (b == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		cout << Time::currenttime;
	}
}

void Callbacks::resize_callback(GLFWwindow* window, int w, int h) 
{
	glfwSetWindowSize(window, w, w);
	glViewport(0, 0, w, w);
}

void Callbacks::scroll_callback(GLFWwindow* window, double x, double y) 
{
	
}


void Callbacks::initCallbacks() 
{	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursorpos_callback);
	glfwSetMouseButtonCallback(window, mouseB_callback);
	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetScrollCallback(window, scroll_callback);
}









