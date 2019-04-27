#include "FirstInitHeader.h"
#include "delegate.h"

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



void func(int x,int y)
{
	cout <<"X: "<<x << "\tY: " << y<<endl;
}


int main()
{
	Callbacks::mouse_click_event.Add(func);

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

	GLuint U_Global_Matrix = userGl::glUniformBuffer(128, 1);
	GLuint U_Global_MatProps = userGl::glUniformBuffer(32, 2);

	userGl::glUniformData(U_Global_MatProps, 4, 0, 0.1f);
	userGl::glUniformData(U_Global_MatProps, 4, 4, 0.8f);
	userGl::glUniformData(U_Global_MatProps, 4, 8, 0.3f);
	userGl::glUniformData(U_Global_MatProps, 4, 12, 32.f);
	userGl::glUniformDataObject(U_Global_Matrix, 64, 64, &Matrix::projection);

	Material model("Default/Model");
	Skybox *skybox = new Skybox("Data/Textures/SkyboxN/oasisnight","tga");
	

	///------------------------------------------------------------------------------------------------------------
	model.BindUniformBuffer("Matrices", 1);
	model.BindUniformBuffer("MatProps", 2);
	model.BindUniformBuffer("Light", 3);
	skybox->BindUniformBuffer("Matrices", 1);


	///-------------------------------------------------------------------------------------------------------------

	GameObject floor(Primitive::Cube(), &model);
	floor.transform->Scale(vec3(30,1,30));
	GLuint grassTex = Texture2D::Texture2D("Data/Textures/grass_1.png");
	floor.material->SetTexture(grassTex, "texture_diffuse");

	GameObject box(Primitive::Cube(), &model);
	box.transform->_position.y += 4;
	box.transform->_position.x += 8;


	GameObject *light = new GameObject();
	DirectionalLight *dL = light->AddComponentR<DirectionalLight>();
	dL->direction = vec3(0, -1, 0);
	dL->transform->_position = vec3(0, 10, 0);
	dL->strengh = 1.f;
	dL->color = vec3(0.85, 0.65, 0.39);
	floor.material->params.stretch = vec2(50, 50);

	userGl::glUniformLights();

	while (!glfwWindowShouldClose(window))
	{
		if (Input::GetKeyDown(GLFW_KEY_ESCAPE))
		{
			goto exit;
		}

		Time::currenttime = glfwGetTime();
		Time::CalculateDelta();
		userGl::ActiveLights();

//-------------------------------------------------------------------------------------//
		glfwPollEvents();
		glClearColor(0.1f, 0.02f, 0.1f,0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera->Draw();
		light->Draw();
		floor.Draw();
		box.Draw();
		
		skybox->Draw();		
//------------------------------------------------------------------------------------//
		userGl::glUniformDataObject(U_Global_MatProps, 16, 16, &Camera::mainCamera->transform->_position);
		userGl::glUniformDataObject(U_Global_Matrix, 64, 0, &Matrix::view);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}


exit:
	delete skybox;
	delete camera;
	delete light;

	glDeleteBuffers(1, &U_Global_Matrix);
	glDeleteBuffers(1, &U_Global_MatProps);
	glDeleteBuffers(1, &userGl::U_Global_LightsPDS);

	glfwTerminate();
	return 0;
}
