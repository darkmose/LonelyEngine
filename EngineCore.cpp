#include "FirstInitHeader.h"
#include "CameraController.h"
#include "Skybox.h"

int SCR_W, SCR_H;
GLbyte _MSAA = 1;


GLFWwindow* window;


int WindowInit() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, _MSAA);
	
	

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

	glfwGetFramebufferSize(window, &SCR_W, &SCR_H);
	glViewport(0, 0, SCR_W, SCR_H);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	GameObject *camera = new GameObject();
	camera->AddComponentR<Camera>();
	camera->AddComponent<CameraController>();
	camera->transform->_position = vec3(1, 3, 1);

	GLuint U_Global_Matrix = glUniformBuffer(128, 1);
	GLuint U_Global_MatProps = glUniformBuffer(32, 2);

	glUniformData(U_Global_MatProps, 4, 0, 0.1f);
	glUniformData(U_Global_MatProps, 4, 4, 0.8f);
	glUniformData(U_Global_MatProps, 4, 8, 0.3f);
	glUniformData(U_Global_MatProps, 4, 12, 32.f);
	glUniformDataObject(U_Global_Matrix, 64, 64, &Matrix::projection);

	Material model("Default/Standart");
	Skybox *skybox = new Skybox("Textures/SkyboxN/purplenebula","tga");
	

	///------------------------------------------------------------------------------------------------------------
	model.BindUniformBuffer("Matrices", 1);
	model.BindUniformBuffer("MatProps", 2);
	model.BindUniformBuffer("Light", 3);
	skybox->BindUniformBuffer("Matrices", 1);


	///-------------------------------------------------------------------------------------------------------------

	GameObject floor(Primitive::Cube(), &model);
	floor.transform->Scale(vec3(30,1,30));
	Texture2D metallTex("Textures/grass_1.png");
	floor.material->SetTexture(&metallTex, "texture_diffuse");

	GameObject box(Primitive::Cube(), &model);
	box.transform->_position.y += 4;

	GameObject *light = new GameObject();
	DirectionalLight *dL = light->AddComponentR<DirectionalLight>();
	dL->direction = vec3(0, -1, 0);
	dL->strengh = 1.f;
	dL->color = vec3(0.85, 0.65, 0.39);
	floor.material->params.stretch = vec2(30, 30);


	mat4 projLight = Matrix::GenOrtho(50, 50, 50, 50, 0, 200);
	mat4 viewLight = lookAt(dL->transform->_position, dL->direction, Transform::up);
	mat4 projL = projLight * viewLight;
	RenderTexture texLight(1024, 1024, GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RGB);
	Material* depth = new Material("Default/Depth");
	


	glUniformLights();

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}

		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();
		ActiveLights();


//-------------------------------------------------------------------------------------//
		glfwPollEvents();
		glClearColor(0.1, 0.02, 0.1, 1);
		
		texLight.ActiveBuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		depth->SetUnifMat4("projView", projL);
		floor.Draw(depth);
		box.Draw(depth);		
		
		texLight.DeactiveBuffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		model.SetUnifMat4("projViewL", projL);
		camera->Draw();
		light->Draw();
		floor.Draw();
		box.Draw();
		
		skybox->Draw();		
//------------------------------------------------------------------------------------//
		glUniformDataObject(U_Global_MatProps, 16, 16, &Camera::mainCamera->transform->_position);
		glUniformDataObject(U_Global_Matrix, 64, 0, &Matrix::view);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


exit:
	delete skybox;
	delete camera;
	delete light;

	glDeleteBuffers(1, &U_Global_Matrix);
	glDeleteBuffers(1, &U_Global_MatProps);
	glDeleteBuffers(1, &U_Global_LightsPDS);

	glfwTerminate();
	return 0;
}
