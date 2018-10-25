#include "FirstInitHeader.h"
#include "CameraController.h"
#include "PlayerController.h"

GLFWwindow* window;
GLfloat vertices[] = {
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

GLfloat quad[] = 
{
   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
   -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f
};
GLfloat postQuad[] = 
{
   -1.0f,  1.0f,  0.0f, 1.0f,
   -1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

   -1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

GLint params[] = { 3,2,3 };
GLint param2[] = { 3,2 };
GLint param3[] = { 2,2 };

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

	Material *sprite = new Material("Default/Sprite",quad,sizeof(quad),GL_STATIC_DRAW,param2, GL_FALSE, GL_TRUE, 2,6);
	Material *postProc = new Material("ForTest/Postprocess",postQuad,sizeof(postQuad),GL_DYNAMIC_DRAW, param3, GL_FALSE, GL_TRUE, 2,6);
	Material *model = new Material("Default/Model");
	Material *vertex2 = new Material("Default/Standart",vertices, sizeof(vertices), GL_DYNAMIC_DRAW, params, GL_FALSE, GL_TRUE, 3, 36);	
	GameObject *camera = new GameObject();

	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();

	GameObject *spr = new GameObject(sprite);
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", *model);

	GameObject *LightCube = new GameObject();
	LightCube->AddComponent<PointLight>(new PointLight(LightCube->transform));

	Texture2D box("Textures/metal.jpg");
	Texture2D trava("Textures/trava.png");

	const int he = 100;
	const int wi = 100;

	vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f,1, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 1, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 1, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f,1, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 1, -0.6f));


	Texture2D::FilterTextures(GL_CLAMP_TO_EDGE, GL_LINEAR);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LightCube->transform->_position = vec3(4);
	camera->transform->_position = vec3(1, 3, 1);
	spr->transform->_position = Transform::up;
	city->transform->_position.y++;

	GLuint buffer;
	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);

	Texture2D *rTex = new Texture2D(x, y,GL_RGB); //GL_DEPTH_COMPONENT, GL_STENCIL_INDEX, GL_DEPTH24_STENCIL8
	rTex->Active(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0);
	
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, x, y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GameObject* rSprite = new GameObject(postProc);

	
	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}

		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();		
		
		glfwPollEvents();

		glBindFramebuffer(GL_FRAMEBUFFER, buffer);

		glClearColor(0.10f, 0.11f, 0.15f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glEnable(GL_DEPTH_TEST);
		box.Active();
		camera->Draw();
		city->Draw();
		trava.Active();

		for (size_t i = 0; i < vegetation.size(); i++)
		{
			spr->transform->_position = vegetation[i];
			spr->material->ActiveShader();
			spr->material->SetUnifVec3("col", vec3(0.5f,float(i)/10,0.5f));
			spr->Draw();
		}
		
		box.Active();
		LightCube->Draw();

		if (Input::GetKey(GLFW_KEY_UP))
			LightCube->GetComponent<PointLight>()->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			LightCube->GetComponent<PointLight>()->strengh -= Time::deltaTime;	
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.10f, 0.11f, 0.15f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		rTex->Active();
		rSprite->Draw();

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	exit:

	delete vertex2;
	delete rTex;
	delete postProc;
	delete sprite;
	delete spr;
	delete model;
	glDeleteFramebuffers(1, &buffer);
	glDeleteRenderbuffers(1, &rbo);
	delete city;
	delete LightCube;
	delete camera;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();

	glfwTerminate();
	return 0;
}
