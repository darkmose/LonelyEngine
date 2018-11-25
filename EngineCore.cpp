#include "FirstInitHeader.h"
#include "CameraController.h"
#include "Skybox.h"

int SCR_W, SCR_H;

vector<GLfloat> cubeVert =
{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

GLFWwindow* window;

int WindowInit() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 1);
	
	

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
	glfwGetFramebufferSize(window, &SCR_W, &SCR_H);
	glViewport(0, 0, SCR_W, SCR_H);

	

	return 1;
}

int main()
{
	if (WindowInit() == -1)
	{
		cout << "OpenGL Init error!";
		return -1;
	}
	
	Matrix::projection = Matrix::GenPerspective(SCR_W, SCR_H, 0.1f, 400.f);

	Callbacks::initCallbacks(window);
	///
	vector<string> faces =
	{
		"Textures/Skybox/right.jpg",
		"Textures/Skybox/left.jpg",
		"Textures/Skybox/top.jpg",
		"Textures/Skybox/bottom.jpg",
		"Textures/Skybox/front.jpg",
		"Textures/Skybox/back.jpg"
	};
	
	Skybox *skybox = new Skybox(faces);
	///
	Material *model = new Material("Default/ModelShadow");
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", model);
	city->transform->_position.y++;
	///
	GameObject *camera = new GameObject();	
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();
	camera->transform->_position = vec3(1, 3, 1);
	///
	GameObject *LightCube = new GameObject();
	DirectionalLight *dLight = LightCube->AddComponentR<DirectionalLight>(new DirectionalLight());
	dLight->strengh = 2;
	dLight->direction = vec3(-1, -4, 0);
	dLight->color = vec3(1,0.86f,0.55f);
	///
	GLuint MatrixGlobalShader = glCreateUnifBuffer(128, 1);
	glSetUnifVariable(MatrixGlobalShader, 64, 64, &Matrix::projection);
	model->SetShaderUnifBlockBind("Matrices", 1);
	skybox->SetShaderUnifBlockBind("Matrices", 1);
	GLuint CameraGlobalShader = glCreateUnifBuffer(16, 2);
	model->SetShaderUnifBlockBind("Camera", 2);
	skybox->SetShaderUnifBlockBind("Camera", 2);
	GLuint MatPropsGlobalShafer = glCreateUnifBuffer(16, 3);
	model->SetShaderUnifBlockBind("MatProps", 3);
	glSetUnifVariable(MatPropsGlobalShafer, 0,	4, &model->matProps.ambient);
	glSetUnifVariable(MatPropsGlobalShafer, 4, 4, &model->matProps.diffuse);
	glSetUnifVariable(MatPropsGlobalShafer, 8, 4, &model->matProps.specular);
	glSetUnifVariable(MatPropsGlobalShafer, 12, 4, &model->matProps.specularStr);
	///
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int DPTH_W = 1024, DPTH_H = 1024;

	RenderTexture depthMap(DPTH_W, DPTH_H, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, GL_FLOAT);

	mat4 lightView = lookAt(vec3(0,30,0), vec3(0,0,0), Transform::up);
	mat4 lightProj = Matrix::GenOrtho(-10.,10.,-10.,10.,0.1,40.);
	mat4 lightSpaceMatrix = lightProj * lightView;
	Material depth("Default/Depth");
	depth.SetShaderUnifBlockBind("Matrices", 1);
	
	Material forScreen("ForTest/Screen");

	Mesh * screen = Primitive::Quad();
	Texture2D testTex("Textures/testDepth.png");
	vec3 _scale = vec3(1);
	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}		
		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();


//-------------------------------------------------------------------------------------//

		glfwPollEvents();
		if (Input::GetKey(GLFW_KEY_UP))
			dLight->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			dLight->strengh -= Time::deltaTime;
		
		depthMap.ActiveBuffer();
		glViewport(0, 0, DPTH_W, DPTH_H);
		glClear(GL_DEPTH_BUFFER_BIT);

		depth.ActiveShader();
		depth.SetUnifMat4("lightSpaceMatrix", lightSpaceMatrix);
		city->Draw(&depth);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCR_W, SCR_H);
		glClearColor(0.10f, 0.11f, 0.14f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			

		model->ActiveShader();
		model->SetUnifMat4("lightSpaceMatrix", lightSpaceMatrix);
		model->SetUnifInt("shadowMap", 5);

///test

		depthMap.Active(5);
		forScreen.ActiveShader();
		forScreen.SetUnifInt("_main", 5);
		screen->Draw(&forScreen);
		
		//city->Draw();	
		camera->Draw();
		LightCube->Draw();

//------------------------------------------------------------------------------------//
		skybox->Draw();

		glSetUnifVariable(CameraGlobalShader, 0, 16, &Camera::mainCamera->transform->_position);
		glSetUnifVariable(MatrixGlobalShader, 0, 64, &Matrix::view);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


exit:
	delete skybox;
	delete model;
	delete city;
	delete LightCube;
	delete camera;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();
	faces.clear();
	cubeVert.clear();
	glDeleteBuffers(1, &MatrixGlobalShader);
	glDeleteBuffers(1, &CameraGlobalShader);

	glfwTerminate();
	return 0;
}
