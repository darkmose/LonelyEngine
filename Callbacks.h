#pragma once


static class Callbacks 
{	
private:
	static GLfloat lastX, lastY;
	static GLFWwindow* window;
	static vec2 deltaMouse;
	static Camera* camera;
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

	Callbacks(GLFWwindow* window, Camera* camera);
	static void do_movement(float);	
	static void initCallbacks();
};


inline Callbacks::Callbacks(GLFWwindow * _window, Camera * _camera)
{
	camera = _camera;
	window = _window;
}

GLfloat Callbacks::lastX;
GLfloat Callbacks::lastY;
GLFWwindow* Callbacks::window;
vec2 Callbacks::deltaMouse;
Camera* Callbacks::camera;
bool Callbacks::keys[400];
GLfloat Callbacks::cameraSpeed;
bool Callbacks::mods[10];
float Callbacks::speed = 1.f;


void Callbacks::do_movement(float delta)
{
	cameraSpeed = delta * 5* speed;
	

	if (keys[GLFW_KEY_W])
		camera->Translate(camera->Forward(cameraSpeed));
	if (keys[GLFW_KEY_S])
		camera->Translate(camera->Forward(-cameraSpeed));
	if (keys[GLFW_KEY_A])
		camera->Translate(camera->Right(-cameraSpeed));
	if (keys[GLFW_KEY_D])
		camera->Translate(camera->Right(cameraSpeed));
	if (keys[GLFW_KEY_ESCAPE])
		glfwTerminate();
	if (keys[340])
		speed = 2.f;
	else speed = 1.f;
	if (keys[GLFW_KEY_SPACE])
		camera->Translate(vec3(0, 4 * delta, 0));
	if (keys[GLFW_KEY_F])
		camera->Translate(vec3(0, -4 * delta, 0));
	
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
	camera->Look(deltaMouse.y, deltaMouse.x);
	lastX = xpos;
	lastY = ypos;
}

void Callbacks::mouseB_callback(GLFWwindow* window, int b, int action, int mods)
{
	if (b == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		
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









