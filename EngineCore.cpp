#include "FirstInitHeader.h"
#include "CameraController.h"
#include "Skybox.h"


GLFWwindow* window;

int WindowInit() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	

	window = glfwCreateWindow(1280, 760, "LONELY ENGINE", nullptr, nullptr);
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
	glfwSetCursorPos(window, w / 2, h / 2);
	glViewport(0, 0, w, h);

	

	return 1;
}

int main()
{
	if (WindowInit() == -1)
	{
		cout << "OpenGL Init error!";
		return -1;
	}
	
	int x, y;
	glfwGetWindowSize(window, &x, &y);
	Matrix::SetProjection(float(x), float(y), true);

	Callbacks::initCallbacks(window);

	vector<string> faces =
	{
		"Textures/Skybox/right.jpg",
		"Textures/Skybox/left.jpg",
		"Textures/Skybox/top.jpg",
		"Textures/Skybox/bottom.jpg",
		"Textures/Skybox/front.jpg",
		"Textures/Skybox/back.jpg"
	};


	//Skybox *skybox = new Skybox(faces);

	//Material *postProc = new Material("ForTest/Postprocess");
	Material *model = new Material("Default/Model");
	//Material *vertex2 = new Material("Default/Standart");	
	GameObject *camera = new GameObject();
	
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", model);

	GameObject *LightCube = new GameObject();
	LightCube->AddComponent<DirectionalLight>(new DirectionalLight());

	//Texture2D box("Textures/metal.jpg");
	//vertex2->SetSingleTexture(&box,"texture_diffuse");

	//GameObject *cube = new GameObject(vertex2, Primitive::Cube());
	//cube->transform->_position += vec3(1, 5, 1);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LightCube->transform->_position = vec3(4);
	camera->transform->_position = vec3(1, 3, 1);
	city->transform->_position.y++;

	//RenderTexture *rTex = new RenderTexture(x, y, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RGB);
	//Sprite *mirror = new Sprite();
	//mirror->SetTexture(rTex);

	//	GameObject *mirCam = new GameObject();
	//	mirCam->AddComponent<Camera>(new Camera(mirCam->transform)); //Сделать автоматический возврат адреса при создании

	//Camera *mainCam = camera->GetComponent<Camera>();
	//Camera *renderCam = mirCam->GetComponent<Camera>();
	
	//mainCam->SetMain();

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}
		
		glfwPollEvents();
		if (Input::GetKey(GLFW_KEY_UP))
			LightCube->GetComponent<DirectionalLight>()->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			LightCube->GetComponent<DirectionalLight>()->strengh -= Time::deltaTime;


		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();				
		
//		rTex->ActiveBuffer();     //renderTexture On

		//renderCam->SetMain();
		glClearColor(0.10f, 0.11f, 0.14f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		city->Draw();

		//box.Active();
		//cube->Draw();		

		LightCube->Draw();
	//	skybox->Draw();

	//	rTex->DeactiveBuffer();		//renderTexture Off
		
	/*	
		glClearColor(0.10f, 0.11f, 0.14f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		box.Active();
		camera->Draw();
		city->Draw();
		cube->Draw();

		box.Active();
		LightCube->Draw();

		skybox->Draw();
		mirror->DrawR();*/
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	exit:

//	delete skybox;
	//delete vertex2;
	//delete rTex;
//	delete postProc;
	delete model;
	delete city;
	delete LightCube;
	delete camera;
	//delete cube;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();

	glfwTerminate();
	return 0;
}
