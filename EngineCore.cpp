#include "FirstInitHeader.h"
#include "CameraController.h"
#include "Skybox.h"


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
	
	Matrix::projection = Matrix::GenPerspective(float(x), float(y));

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
	///
	GameObject *camera = new GameObject();	
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();
	camera->transform->_position = vec3(1, 3, 1);
	///
	GameObject *LightCube = new GameObject();
	DirectionalLight *dLight = LightCube->AddComponentR<DirectionalLight>(new DirectionalLight());
	dLight->strengh = 4;
	dLight->color = vec3(1, 0.78f, 0.5f);
	dLight->direction = vec3(-5, -1, 0);
	///
#pragma region GlobalUniforms

	GLuint MatrixGlobalShader = glCreateUnifBuffer(128, 1);
	glSetUnifVariable(MatrixGlobalShader, 64, 64, &Matrix::projection);
	model->SetShaderUnifBlockBind("Matrices", 1);
	skybox->SetShaderUnifBlockBind("Matrices", 1);
	GLuint CameraGlobalShader = glCreateUnifBuffer(16, 2);
	model->SetShaderUnifBlockBind("Camera", 2);
	skybox->SetShaderUnifBlockBind("Camera", 2);
	GLuint MatPropsGlobalShafer = glCreateUnifBuffer(16, 3);
	model->SetShaderUnifBlockBind("MatProps", 3);
	glSetUnifVariable(MatPropsGlobalShafer, 0, 4, &model->matProps.ambient);
	glSetUnifVariable(MatPropsGlobalShafer, 4, 4, &model->matProps.diffuse);
	glSetUnifVariable(MatPropsGlobalShafer, 8, 4, &model->matProps.specular);
	glSetUnifVariable(MatPropsGlobalShafer, 12, 4, &model->matProps.specularStr);

#pragma endregion	
	///
	const GLuint W = 1024, H = 1024;
	RenderTexture *depthMap = new RenderTexture(W, H, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	mat4 shadowProj = Matrix::GenOrtho(-100.f, 100.f, -100.f, 100.f, 0.1f, 50.f);
	mat4 lightView = lookAt(vec3(0, 50, 0),vec3(0.0f, 0.0f, 0.0f),vec3(0.0f, 1.0f, 0.0f));
	mat4 lightSpaceMatrix = shadowProj * lightView;

	Material *depthMaterial = new Material("Default/Depth");
	
	///
	Texture2D *box = new Texture2D("Textures/Box.jpg");
	GameObject* cube = new GameObject(model, Primitive::Cube());
	cube->transform->_position.y += 5;
	///
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	glClearColor(0.10f, 0.11f, 0.14f, 1);
	Mesh *depthMesh = Primitive::Quad();
	Material screen("ForTest/Screen");

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
		
		//glViewport(0, 0, W, H);
		//depthMap->ActiveBuffer();
		//glEnable(GL_DEPTH_TEST);
		//glClear(GL_DEPTH_BUFFER_BIT);
		//depthMaterial->ActiveShader();
		//depthMaterial->SetUnifMat4("lightSpaceMatrix", lightSpaceMatrix);
		//city->Draw(depthMaterial);
		//cube->Draw(depthMaterial);

		//glViewport(0, 0, x, y);
		//depthMap->DeactiveBuffer();
		//glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		//depthMap->Active(GL_TEXTURE5);
		//screen.SetUnifInt("_main", 5);
		depthMesh->Draw(&screen);	
		
		
		/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		camera->Draw();
		LightCube->Draw();
		city->material->ActiveShader();
		city->material->SetUnifInt("shadowMap", 7);
		city->material->SetUnifMat4("lightSpaceMatrix", lightSpaceMatrix);
		city->Draw();	
		box->Active(GL_TEXTURE0);
		cube->Draw();
*/


//------------------------------------------------------------------------------------//
		//skybox->Draw();

		glSetUnifVariable(CameraGlobalShader, 0, 16, &Camera::mainCamera->transform->_position);
		glSetUnifVariable(MatrixGlobalShader, 0, 64, &Matrix::view);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


exit:
	delete depthMap;
	delete depthMaterial;
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
