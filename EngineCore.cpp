#include "FirstInitHeader.h"
#include "GLMath.h"
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Callbacks.h"
#include "VertexData.h"

GLFWwindow* window;
Camera* mainCamera;
Callbacks* _callbacks;
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
GLint params[] = { 3,2 };
GLint lightParam[] = { 3 };

int WindowInit() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	

	window = glfwCreateWindow(1280, 760, "My Window PROJECTTTTTT OPENGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	

	return 1;
}

int main()
{
	if (WindowInit() == -1)
	{
		return -1;
	}
	///Main Variables
	//Camera
	mainCamera = new Camera(vec3(0, 0, 0));
	//Callbacks 
	_callbacks = new Callbacks(window,mainCamera);
	_callbacks->initCallbacks();
	//Material
	VertexData *vertex = new VertexData("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 2, 36, true);
	VertexData *lights = new VertexData("Default/Light",vertices, sizeof(vertices), GL_STATIC_DRAW, lightParam, GL_FALSE, GL_TRUE, 1, 36,false);
	//Texture
	Texture2D box("Textures/box.jpg", SOIL_LOAD_RGB, GL_RGB, GL_RGB);
	box.Active();
	//MatrixGL
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	MatGl matGl(float(x),float(y), true);

	const int he = 30;
	const int wi = 30;

	vec3 map[wi][he];
	for (size_t i = 0; i < wi; i++)
	{
		for (size_t k = 0; k < he; k++)
		{
			map[i][k] = vec3(i, sin(float(i)) / 10 + sin(float(k))/3, k);
		}
	}


	glEnable(GL_DEPTH_TEST);
	mainCamera->SetPosition(vec3(0, 1, 0));
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glfwPollEvents();

		_callbacks->do_movement(deltaTime);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		matGl.view = mainCamera->View();
		
		for (size_t i = 0; i < wi; i++)
		{
			for (size_t k = 0; k < he; k++)
			{				
				matGl.model = translate(mat4(), map[i][k]);
				glUniformMatrix4fv(glGetUniformLocation(vertex->sProgram(), "transform"), 1, GL_FALSE, value_ptr(matGl.GlobalMatrix()));
				vertex->Draw();
			}

		}
		matGl.model = translate(mat4(), vec3(1,9,1));
		glUniformMatrix4fv(glGetUniformLocation(lights->sProgram(), "transform"), 1, GL_FALSE, value_ptr(matGl.GlobalMatrix()));
		lights->Draw();

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

		

	glfwTerminate();
	return 0;
}
