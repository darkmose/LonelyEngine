#include "FirstInitHeader.h"
#include "TestClass.h"

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

GLint params[] = { 3,2,3 };

GLint lightParam[] = { 3 };
GLfloat vertices2[] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};


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
	//MatrixGL
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	Matrix::SetProjection(float(x), float(y), true);
	//Callbacks 
	Callbacks::initCallbacks(window);
	//Material
	Material *outline = new Material("ForTest/Outline", vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);
	Material *vertex = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);
	Material *model = new Material("Default/Model");
	Material *vertex2 = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);
	Material *material = new Material("Default/Color", vertices2, sizeof(vertices2), GL_STATIC_DRAW, lightParam, GL_FALSE, GL_TRUE, 1, 36);
	

	//GameObjects
	GameObject *LightCube = new GameObject(material);
	LightCube->AddComponent<PointLight>(new PointLight(LightCube->transform));
	LightCube->AddComponent<TestClass>(new TestClass());

	GameObject *camera = new GameObject();
	camera->AddComponent<Camera>(new Camera(&camera->transform));
	GameObject *floor = new GameObject(vertex);
	GameObject *CubeBoxOutline = new GameObject(vertex2);
	
	//Texture
	Texture2D box("Textures/metal.jpg");

	box.Active();


	const int he = 100;
	const int wi = 100;



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	LightCube->transform._scale = vec3(0.4f);
	LightCube->transform._position = vec3(4);

	floor->transform.Scale(vec3(wi, 1, he));
	floor->transform._position = vec3(0, 0, 0);
	floor->material->params.stretch = vec2(wi, he);

	CubeBoxOutline->transform._position.y = 3;
	CubeBoxOutline->transform._position.z = 3;

	camera->transform._position = vec3(1, 3, 1);

	while (!glfwWindowShouldClose(window))
	{
		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();
		
		
	
		glfwPollEvents();
		Callbacks::do_movement();		
		
		glClearColor(0.10f, 0.11f, 0.15f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);			

		glStencilMask(0x00);	

		box.Active();
		floor->Draw();
		camera->Draw();

		box.Active();
		LightCube->Draw();

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		CubeBoxOutline->transform.Scale(vec3(1));
		CubeBoxOutline->material = vertex2;
		CubeBoxOutline->Draw();



		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		CubeBoxOutline->transform.Scale(vec3(1.1f));
		CubeBoxOutline->material = outline;
		CubeBoxOutline->material->ActiveShader();
		CubeBoxOutline->material->SetUnifVec4("col", vec4(0.78f, 0.56f, 0.07f, 1.f));
		CubeBoxOutline->Draw();

		if (Input::GetKey(GLFW_KEY_UP))
			LightCube->GetComponent<PointLight>()->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			LightCube->GetComponent<PointLight>()->strengh -= Time::deltaTime;	
		

		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	delete[] vertex;
	delete[] floor;
	delete[] LightCube;
	delete[] camera;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();


	glfwTerminate();
	return 0;
}
