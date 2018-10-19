#include "FirstInitHeader.h"
#include "CameraController.h"
#include "PlayerController.h"

GLFWwindow* window;
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,  1.0f,  0.0f
};

GLfloat quad[] = 
{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f
};

GLint params[] = { 3,2,3 };

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
	
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	Matrix::SetProjection(float(x), float(y), true);

	Callbacks::initCallbacks(window);

	Material *outline = new Material("ForTest/Outline", vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);
	Material *vertex = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);
	Material *vertex2 = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);	

	GameObject *camera = new GameObject();
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();

	GameObject *floor = new GameObject(vertex);

	GameObject *LightCube = new GameObject();
	LightCube->AddComponent<PointLight>(new PointLight(LightCube->transform));

	Texture2D box("Textures/metal.jpg");
	box.Active();


	const int he = 100;
	const int wi = 100;


	glEnable(GL_DEPTH_TEST);
	LightCube->transform->_position = vec3(4);
	floor->transform->Scale(vec3(wi, 1, he));
	floor->transform->_position = vec3(0, 0, 0);
	floor->material->params.stretch = vec2(wi, he);
	camera->transform->_position = vec3(1, 3, 1);
	

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}

		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();		
	
		glfwPollEvents();
		
		glClearColor(0.10f, 0.11f, 0.15f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			

		box.Active();
		floor->Draw();
		camera->Draw();


		box.Active();
		LightCube->Draw();

		if (Input::GetKey(GLFW_KEY_UP))
			LightCube->GetComponent<PointLight>()->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			LightCube->GetComponent<PointLight>()->strengh -= Time::deltaTime;	
	

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	exit:

	delete outline;
	delete vertex2;
	delete vertex;
	delete floor;
	delete LightCube;
	delete camera;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();

	glfwTerminate();
	return 0;
}
