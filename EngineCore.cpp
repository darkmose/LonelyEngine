#include "FirstInitHeader.h"
#include "Light.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Material.h"
#include "Matrix.h"
#include "Camera.h"
#include "Transform.h"
<<<<<<< HEAD
#include "Light.h"
#include "Mesh.h"
#include "Model.h"
=======
>>>>>>> parent of 065523d... 7
#include "GameObj.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Callbacks.h"




GLFWwindow* window;
Camera* mainCamera;
Callbacks* _callbacks;


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
	//Camera
	mainCamera = new Camera(vec3(0, 0, 0));
	//Callbacks 
	_callbacks = new Callbacks(window);
	_callbacks->initCallbacks();
	//Material
	Material *vertex = new Material("Default/Standart");
	Material *material = new Material("Default/Light");

	//GameObjects
<<<<<<< HEAD
	GameObject *LightCube = new GameObject(material);
	LightCube->AddComponent("Light", new DirectionalLight(vec3(-1,-1,-1)));


	GameObject *CubeBox = new GameObject(vertex);
	GameObject *ModelObj = new GameObject(vertex,"Models/suit/nanosuit.obj");

	ModelObj->transform._position += vec3(4, 5, 4);
=======
	GameObj *LightCube = new GameObj(material);
	GameObj *LC2 = new GameObj(*LightCube);
	GameObj *LC3 = new GameObj(*LightCube);
	GameObj *LC4 = new GameObj(*LightCube);
	//LightCube->AddComponent("PL1", new PointLight(LightCube->transform));
	LightCube->AddComponent("DirL", new DirectionalLight(vec3(1,-1,0)));
	//LC2->AddComponent("PL2", new PointLight(LightCube->transform));
	//LC3->AddComponent("PL3", new PointLight(LightCube->transform));
	//LC4->AddComponent("PL4", new PointLight(LightCube->transform));

	GameObj *CubeBox = new GameObj(vertex);
>>>>>>> parent of 065523d... 7
	
	//Texture



	const int he = 100;
	const int wi = 100;



	glEnable(GL_DEPTH_TEST);
	mainCamera->transform._position = vec3(0, 1.5f, 0);
	LightCube->transform._scale = vec3(0.4f);
	LightCube->transform._position = vec3(4);
	DirectionalLight *d = (DirectionalLight*)LightCube->GetComponent("DirL");
	CubeBox->transform.Scale(vec3(wi, 1, he));
	CubeBox->transform._position = vec3(0, 0, 0);
	CubeBox->material->params.stretch = vec2(wi, he);
	d->color = vec3(0, 1, 0);

	GLbyte sss = 0;

	while (!glfwWindowShouldClose(window))
	{
		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();

		glfwPollEvents();
		_callbacks->do_movement();
		
		glClearColor(0.10f, 0.11f, 0.15f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		mainCamera->View();
		
		sss++;
		 
		if ( sss%15 == 0)
		{
			cout << "FPS:  " << 1 / Time::deltaTime << endl;
		}

		CubeBox->Draw();
		ModelObj->Draw();
		LightCube->Draw();		
	//	LC2->Draw();
	//	LC3->Draw();
	//	LC4->Draw();

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	delete[] vertex;
	delete[] CubeBox;
	delete[] LightCube;


	glfwTerminate();
	return 0;
}
