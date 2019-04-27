#pragma once

class CameraController : public Component
{
private:
	GLfloat cameraSpeed;
	GLfloat speed = 1.f;
	Camera* camera;
	void myFunc();
	vec2 deltaMouse;
	double lastX, lastY;
public:
	void Awake() 
	{
		camera = Camera::mainCamera;
	}
	void Update();
};



void CameraController::myFunc()
{
	vec2 mousePos = Input::mousePos();
	deltaMouse = vec2((mousePos.x - lastX), (lastY - mousePos.y));
	Camera::mainCamera->Look(deltaMouse.y, deltaMouse.x);
	lastX = mousePos.x;
	lastY = mousePos.y;

	cameraSpeed = Time::deltaTime * 5 * speed;

	if (Input::GetKey(GLFW_KEY_W))
		camera->transform->TranslatePos(camera->Forward(cameraSpeed));
	if (Input::GetKey(GLFW_KEY_S))
		camera->transform->TranslatePos(camera->Forward(-cameraSpeed));
	if (Input::GetKey(GLFW_KEY_A))
		camera->transform->TranslatePos(camera->Right(-cameraSpeed));
	if (Input::GetKey(GLFW_KEY_D))
		camera->transform->TranslatePos(camera->Right(cameraSpeed));
	if (Input::GetKeyDown(GLFW_KEY_DOWN))
	{
		
	}

	
	if (Input::GetKey(340))
		speed = 2.f;
	else speed = 1.f;
	if (Input::GetKey(GLFW_KEY_SPACE))
		camera->transform->TranslatePos(vec3(0, 4 * Time::deltaTime*speed, 0));
	if (Input::GetKey(GLFW_KEY_F))
		camera->transform->TranslatePos(vec3(0, -4 * Time::deltaTime*speed, 0));
}

void CameraController::Update()
{
	myFunc();
}
