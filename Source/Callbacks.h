#pragma once
#include "delegate.h"

static class Callbacks 
{	
private:
	static GLfloat lastX, lastY;
	static vec2 deltaMouse;
	static bool keys[400];
	static unsigned char state[400];
	static bool mods[10];
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouseB_callback(GLFWwindow* window, int b, int action, int mods);
	static void resize_callback(GLFWwindow* window, int w, int h);
	static void scroll_callback(GLFWwindow* window, double x, double y);
public:
	static GLFWwindow* _window;
	static bool getKey(int nKey);
	static bool getMod(int nMod);
	static unsigned char getState(int nKey);
	static void setState(int nKey, unsigned char state);
	static void initCallbacks(GLFWwindow*);
	static delegate<int, int> mouse_click_event;
	static vec2 mousePos;
};

GLFWwindow* Callbacks::_window;
GLfloat Callbacks::lastX;
GLfloat Callbacks::lastY;
vec2 Callbacks::deltaMouse;
bool Callbacks::keys[400];
bool Callbacks::mods[10];
unsigned char Callbacks::state[400];
delegate<int, int> Callbacks::mouse_click_event;
vec2 Callbacks::mousePos;




void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) 
	{
		keys[key] = true;
		state[key] = GLFW_PRESS;
	}
	else if (action == GLFW_RELEASE) 
	{
		keys[key] = false;
		state[key] = GLFW_RELEASE;
	}	
}

void Callbacks::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{		
	mousePos = vec2(xpos, ypos);
}

void Callbacks::mouseB_callback(GLFWwindow* window, int b, int action, int mods)
{
	mouse_click_event(lastX,lastY);
}

void Callbacks::resize_callback(GLFWwindow* window, int w, int h) 
{

}

void Callbacks::scroll_callback(GLFWwindow* window, double x, double y) 
{
	
}

inline bool Callbacks::getKey(int nKey)
{
	return keys[nKey];
}

inline bool Callbacks::getMod(int nMod)
{
	return mods[nMod];
}

inline unsigned char Callbacks::getState(int nKey)
{
	return state[nKey];
}

inline void Callbacks::setState(int nKey, unsigned char _state)
{
	state[nKey] = _state; 
}


void Callbacks::initCallbacks(GLFWwindow* window) 
{	
	_window = window;
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursorpos_callback);
	glfwSetMouseButtonCallback(window, mouseB_callback);
	glfwSetWindowSizeCallback(window, resize_callback);
	glfwSetScrollCallback(window, scroll_callback);
	for (size_t i = 0; i < 400; i++)
	{
		state[i] = GLFW_PRESS;
	}
}









