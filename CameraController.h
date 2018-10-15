#pragma once

class CameraController : public Component
{
private:
	GLfloat cameraSpeed;
	GLfloat speed = 1.f;
	Camera* camera;
	void myFunc();
	void Awake()
	{
		camera = gameObject->GetComponent<Camera>();
	}
public:
	void Update();
};



void CameraController::myFunc()
{
	cameraSpeed = Time::deltaTime * 5 * speed;

	if (Input::GetKey(GLFW_KEY_W))
		camera->transform->TranslatePos(camera->Forward(cameraSpeed));
	if (Input::GetKey(GLFW_KEY_S))
		camera->transform->TranslatePos(camera->Forward(-cameraSpeed));
	if (Input::GetKey(GLFW_KEY_A))
		camera->transform->TranslatePos(camera->Right(-cameraSpeed));
	if (Input::GetKey(GLFW_KEY_D))
		camera->transform->TranslatePos(camera->Right(cameraSpeed));

	if (Input::GetKey(340))
		speed = 2.f;
	else speed = 1.f;
	if (Input::GetKey(GLFW_KEY_SPACE))
		camera->transform->TranslatePos(vec3(0, 4 * Time::deltaTime, 0));
	if (Input::GetKey(GLFW_KEY_F))
		camera->transform->TranslatePos(vec3(0, -4 * Time::deltaTime, 0));
}

void CameraController::Update()
{
	myFunc();
}
