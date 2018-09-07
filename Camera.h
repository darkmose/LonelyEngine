#pragma once

class Camera
{
private:
	vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
	vec3 cameraPos = vec3(0, -2, 0);
	vec3 cameraUp = vec3(0, 1, 0);
	vec3 direction;
	GLfloat p = 0.f, y = -90.f;

public:
	void Look(GLfloat, GLfloat);
	mat4 View();
	Camera(vec3);
	void SetPosition(vec3);
	void Translate(vec3);
	vec3 Forward(float);
	vec3 Right(float);
};


inline Camera::Camera(vec3 position) : cameraPos(position) {}

 void Camera::SetPosition(vec3 pos)
{
	cameraPos = pos;
}

 void Camera::Translate(vec3 vectorTranslate)
{
	cameraPos += vectorTranslate;
}

 vec3 Camera::Forward(float scale = 1)
{
	return vec3(cameraFront.x,0,cameraFront.z)*scale;
}

 vec3 Camera::Right(float scale = 1)
{
	 vec3 r = normalize(glm::cross(cameraFront, cameraUp))*scale;
	 return vec3(r.x,0,r.z);
}

void Camera::Look(GLfloat pitch, GLfloat yaw)
{
	p += pitch*deltaTime*10;
	y += yaw*deltaTime*10;
	if (p > 89.0f)
		p = 89.0f;
	if (p < -89.0f)
		p = -89.0f;	
	
	direction.x = cos(glm::radians(y)) * cos(glm::radians(p));
	direction.y = sin(glm::radians(p));
	direction.z = sin(glm::radians(y)) * cos(glm::radians(p));
	cameraFront = normalize(direction);
}

mat4 Camera::View() 
{	
	return lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
}


