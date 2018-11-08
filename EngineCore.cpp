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
	Material *model = new Material("Default/Model");
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", model);
	city->transform->_position.y++;
	///
	GameObject *camera = new GameObject();	
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();
	camera->transform->_position = vec3(1, 3, 1);
	///
	Material *newM = new Material("Default/Color");
	newM->params.objectCol = vec3(0.25f, 0.71f, 0.71f);
	GameObject *newG = new GameObject(newM, Primitive::Quad());
	newG->transform->_position = vec3(1, 5, 10);
	///
	GameObject *LightCube = new GameObject();
	PointLight *pLight = LightCube->AddComponentR<PointLight>(new PointLight(LightCube->transform));
	pLight->strengh = 4;
	///
	GLuint MatrixGlobalShader = glCreateUnifBuffer(128, 1);
	glSetUnifVariable(MatrixGlobalShader, 64, 64, &Matrix::projection);
	model->SetShaderUnifBlockBind("Matrices", 1);
	newM->SetShaderUnifBlockBind("Matrices", 1);
	skybox->SetShaderUnifBlockBind("Matrices", 1);
	GLuint CameraGlobalShader = glCreateUnifBuffer(16, 2);
	model->SetShaderUnifBlockBind("Camera", 2);
	newM->SetShaderUnifBlockBind("Camera", 2);
	skybox->SetShaderUnifBlockBind("Camera", 2);
	GLuint MatPropsGlobalShafer = glCreateUnifBuffer(16, 3);
	model->SetShaderUnifBlockBind("MatProps", 3);
	glSetUnifVariable(MatPropsGlobalShafer, 0,	4, &model->matProps.ambient);
	glSetUnifVariable(MatPropsGlobalShafer, 4, 4, &model->matProps.diffuse);
	glSetUnifVariable(MatPropsGlobalShafer, 8, 4, &model->matProps.specular);
	glSetUnifVariable(MatPropsGlobalShafer, 12, 4, &model->matProps.specularStr);
	///
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vec3 _scale = vec3(1);
	glEnable(GL_PROGRAM_POINT_SIZE);
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
			pLight->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			pLight->strengh -= Time::deltaTime;				
		
		glClearColor(0.10f, 0.11f, 0.14f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		city->Draw();	
		newG->Draw();
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
	delete newM;
	delete newG;
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
