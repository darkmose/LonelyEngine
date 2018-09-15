#pragma once
#include "Transform.h"

class Camera
{
private:
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 direction;
	GLfloat p = 0.f, y = -90.f;
public:
	static Camera* mainCamera;
	Transform transform;
	void Look(GLfloat, GLfloat);
	void View();
	Camera(vec3);
	vec3 Forward(float);
	vec3 Right(float);
	vec3 Direction();
};

Camera* Camera::mainCamera;

inline Camera::Camera(vec3 position)
{
	mainCamera = this;
	transform._position = vec3(0.f, 0.f, 0.f);	
}


 vec3 Camera::Forward(float scale = 1)
{
	return vec3(cameraFront.x,0,cameraFront.z)*scale;
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
	Matrix::view = lookAt(transform._position, (transform._position + cameraFront), Transform::up);
}


