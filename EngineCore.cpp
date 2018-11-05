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

	vector<string> faces =
	{
		"Textures/Skybox/right.jpg",
		"Textures/Skybox/left.jpg",
		"Textures/Skybox/top.jpg",
		"Textures/Skybox/bottom.jpg",
		"Textures/Skybox/front.jpg",
		"Textures/Skybox/back.jpg"
	};
	vector<string> ice =
	{
		"Textures/ice.png",
		"Textures/ice.png",
		"Textures/ice.png",
		"Textures/ice.png",
		"Textures/ice.png",
		"Textures/ice.png",
	};
	

	//==========================================
	Mesh* iceBlock = new Mesh({Primitive::_Cube_Pos,Primitive::_Cube_Norm, Primitive::Empty });
	Material* reflectMaterial = new Material("Default/Reflective");
	Texture2D *iceTexCube = new Texture2D(ice);
	//===========================================
	
	
	Skybox *skybox = new Skybox(faces);

	Material *model = new Material("Default/Model");
	Material *modelR = new Material("ForTest/ModelGlass");
	GameObject *city = new GameObject("Models/city/Street environment_V01.obj", model);
	city->transform->_position.y++;
	

	GameObject *camera = new GameObject();	
	camera->AddComponent<Camera>(new Camera(camera->transform));
	camera->AddComponent<CameraController>();
	camera->transform->_position = vec3(1, 3, 1);

	GameObject *LightCube = new GameObject();
	PointLight *pLight = LightCube->AddComponentR<PointLight>(new PointLight(LightCube->transform));


	GameObject* nano = new GameObject("Models/suit/nanosuit.obj", modelR);
	nano->transform->_position = vec3(10, 10, 20);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vec3 _scale = vec3(1);

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKey(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}		
		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();

		glfwPollEvents();
//-------------------------------------------------------------------------------------//

		if (Input::GetKey(GLFW_KEY_UP))
			pLight->strengh += Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_DOWN))
			pLight->strengh -= Time::deltaTime;
		if (Input::GetKey(GLFW_KEY_Q))
			_scale += Time::deltaTime;

//-------------------------------------------------------------------------------------//		
		
		glClearColor(0.10f, 0.11f, 0.14f,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		camera->Draw();
		//city->Draw();	

		LightCube->Draw();
		skybox->Draw();
		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->CubeMap());
		nano->Draw();

		reflectMaterial->ActiveShader();
		Matrix::model = translate(mat4(),vec3(3, 4, 3))*scale(mat4(), _scale);
		reflectMaterial->SetUnifMat4("Matrix.model", Matrix::model);
		reflectMaterial->SetUnifMat4("Matrix.view", Matrix::view);
		reflectMaterial->SetUnifMat4("Matrix.projection", Matrix::projection);
		reflectMaterial->SetUnifVec3("cameraPos", camera->transform->_position);
		reflectMaterial->SetUnifInt("Textures.cubeMap", 0);
		reflectMaterial->SetUnifInt("Textures.cube_diffuse", 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->CubeMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, iceTexCube->Texture());

	//	iceBlock->Draw(reflectMaterial, true);

//------------------------------------------------------------------------------------//

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


	exit:

	delete reflectMaterial;
	delete iceTexCube;
	delete iceBlock;
	ice.clear();

	delete skybox;
	delete model;
	delete city;
	delete LightCube;
	delete camera;
	Light::pointLs.clear();
	Light::spotLs.clear();
	Light::dirLs.clear();

	glfwTerminate();
	return 0;
}
