#pragma once

class Camera : public Component
{
private:
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 direction;
	GLfloat p = 0.f, y = -90.f;	
public:
	void Update();
	static Camera* mainCamera;
	void Look(GLfloat, GLfloat);
	void View();
	void SetMain();
	Camera();
	vec3 Forward(float);
	vec3 Right(float);
	vec3 Direction();
	~Camera();
};

Camera* Camera::mainCamera;

inline Camera::Camera()
{
	if (mainCamera == NULL)
	{
		Camera::mainCamera = this;
	}	
}


 vec3 Camera::Forward(float scale = 1)
{
	return normalize(vec3(cameraFront.x,0,cameraFront.z))*scale;
}

 vec3 Camera::Right(float scale = 1)
{
	 vec3 r = normalize(cross(cameraFront, Transform::up))*scale;
	 return vec3(r.x,0,r.z);
}

 inline vec3 Camera::Direction()
 {
	 return cameraFront;
 }

 inline Camera::~Camera()
 {
	 if (mainCamera == this)
	 {
		 mainCamera = NULL;
	 }
	 transform = NULL;
 }


 inline void Camera::Update()
 {
	View();
 }

 void Camera::Look(GLfloat pitch, GLfloat yaw)
{
	p += pitch*Time::deltaTime*10;
	y += yaw*Time::deltaTime*10;
	if (p > 89.0f)
		p = 89.0f;
	if (p < -89.0f)
		p = -89.0f;	
	
	direction.x = cos(glm::radians(y)) * cos(glm::radians(p));
	direction.y = sin(glm::radians(p));
	direction.z = sin(glm::radians(y)) * cos(glm::radians(p));
	cameraFront = normalize(direction);
}

void Camera::View() 
{	
	Matrix::view = lookAt(transform->_position, (transform->_position + cameraFront), Transform::up);
}

inline void Camera::SetMain()
{
	mainCamera = this;
}


