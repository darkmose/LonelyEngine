#include "FirstInitHeader.h"
#include "CameraController.h"
#include "PlayerController.h"


GLFWwindow* window;
vector <GLfloat> vertices = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f
};

vector <GLfloat> postQuad = 
{
   -1.0f,  1.0f,  0.0f, 1.0f,
   -1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

   -1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

vector<GLint> params = { 3,2,3 };
vector<GLint> params2 = { 2,2 };

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
	glfwSetCursorPos(window, w / 2, h / 2);
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

	//Material *postProc = new Material("ForTest/Postprocess",postQuad,sizeof(postQuad),GL_STATIC_DRAW, params2, GL_FALSE, GL_TRUE, 2,6);
	Material *postProc = new Material("ForTest/Postprocess");
	Material *model = new Material("Default/Model");
	//Material *vertex2 = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);	
	Material *vertex2 = new Material("Default/Standart");	
	GameObject *camera = new GameObject();

	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();

	Sprite* spr = new Sprite("Textures/trava.png");
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", model);

	GameObject *LightCube = new GameObject();
	LightCube->AddComponent<PointLight>(new PointLight(LightCube->transform));

	Texture2D box("Textures/metal.jpg");
	vertex2->SetSingleTexture(&box,"texture_diffuse");
	GameObject *cube = new GameObject(vertex2, new Mesh(vertices, vector<GLuint>::vector(), params));
	cube->transform->_position += vec3(1, 5, 1);
	

	const int he = 100;
	const int wi = 100;

	vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f,3, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 3, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 3, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f,3, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 3, -0.6f));

	spr->transform->Scale(vec3(2));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LightCube->transform->_position = vec3(4);
	camera->transform->_position = vec3(1, 3, 1);
	spr->transform->_position = Transform::up;
	city->transform->_position.y++;

	RenderTexture *rTex = new RenderTexture(x, y, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RGB);

	GameObject* rSprite = new GameObject(postProc, new Mesh(postQuad,vector<GLuint>::vector(),params2));

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}
		
		if (Input::GetKey(GLFW_KEY_UP))
			LightCube->GetComponent<PointLight>()->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			LightCube->GetComponent<PointLight>()->strengh -= Time::deltaTime;


		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();		
		
		glfwPollEvents();
		
		rTex->ActiveBuffer();     //renderTexture On

		glClearColor(0.10f, 0.11f, 0.14f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
		glEnable(GL_DEPTH_TEST);

		for (size_t i = 0; i < vegetation.size(); i++)
		{
			spr->transform->_position = vegetation[i]*vec3(i,1,i);
			spr->Draw();
		}
		box.Active();
		camera->Draw();
		city->Draw();
		cube->Draw();
		
		box.Active();
		LightCube->Draw();

		rTex->DeactiveBuffer();		//renderTexture Off

		glClearColor(0.10f, 0.11f, 0.15f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);

		rTex->Active();
		rSprite->material->ActiveShader();
		rSprite->material->SetUnifInt("_case", 2);
		rSprite->mesh->Draw(rSprite->material, true);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	exit:

	delete vertex2;
	delete rTex;
	delete postProc;
	delete spr;
	delete model;
	delete city;
	delete LightCube;
	delete camera;
	delete cube;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();

	glfwTerminate();
	return 0;
}
