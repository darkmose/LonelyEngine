#pragma once
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include <vector>

struct DirectionalL
{
	vec3 direction;
	vec3 color;
	float strengh;
};

struct PointL
{
	vec3 position;
	vec3 color;
	float strengh;
	float Kc;
	float Kl;
	float Kq;
};

struct SpotL
{
	vec3 position;
	vec3 color;
	vec3 direction;
	float strengh;
	float innerCutOff;
	float outerCutOff;
};


class Light : public Component
{
private:
public:
	vec3 color;
	float strengh = 1;
	Light() {}



	static vector<PointL*> pointLs;
	static vector<DirectionalL*> dirLs;
	static vector<SpotL*> spotLs;
};

 vector<PointL*> Light::pointLs(0);
 vector<DirectionalL*> Light::dirLs(0);
 vector<SpotL*> Light::spotLs(0);

 class SpotLight : public Light
 {
 private:
	 int id;
 public:
	 float outerCutOff;
	 float innerCutOff;
	 vec3 direction;
	 vec3 position;
	 SpotLight();
	 ~SpotLight();
	 void Update();
	 void GetParams();
	 SpotL SLight;
 };



 SpotLight::SpotLight()
 {
	 color = vec3(1);
	 strengh = 1.f;
	 outerCutOff = cos(radians(30.f));
	 innerCutOff = cos(radians(20.f));
	 SLight.color = this->color;
	 SLight.direction = Camera::mainCamera->Direction();
	 SLight.position = Camera::mainCamera->transform._position;
	 SLight.innerCutOff = this->innerCutOff;
	 SLight.outerCutOff = this->outerCutOff;
	 SLight.strengh = this->strengh;

	 spotLs.insert(spotLs.end(), &SLight);
	 id = spotLs.size() - 1;
 }


 SpotLight::~SpotLight()
 {
	 spotLs.erase(spotLs.begin() + id);
 }

 inline void SpotLight::Update()
 {
	 if (reset)
	 {
		 GetParams();
		 reset = !reset;
	 }
 }

 inline void SpotLight::GetParams()
 {
	 SLight.color = this->color;
	 SLight.direction = Camera::mainCamera->Direction();
	 SLight.position = Camera::mainCamera->transform._position;
	 SLight.innerCutOff = this->innerCutOff;
	 SLight.outerCutOff = this->outerCutOff;
	 SLight.strengh = this->strengh;
 }


 class PointLight : public Light
 {
 private:
	 float
		 Kc = 1.f,
		 Kl = 0.014f,
		 Kq = 0.0007f;
	 int id;
 public:
	 float radius;
	 Transform * transform;
	 PointLight(Transform&);
	 ~PointLight();
	 void Update();
	 void GetParams();
	 PointL PLight;
 };



 PointLight::PointLight(Transform& transf)
 {
	 transform = &transf;
	 strengh = 1.f;
	 radius = 1.f;
	 color = vec3(1);
	 PLight.color = this->color;
	 PLight.Kc = this->Kc;
	 PLight.Kl = this->Kl / radius * 1.6f;
	 PLight.Kq = this->Kq / radius * 1.6f;
	 PLight.position = this->transform->_position;
	 PLight.strengh = this->strengh;


	 pointLs.insert(pointLs.end(), &PLight);
	 id = pointLs.size() - 1;
 }


 PointLight::~PointLight()
 {
	 delete[] transform;
	 pointLs.erase(pointLs.begin() + id);
 }

 inline void PointLight::Update()
 {
	 if (reset)
	 {
		 GetParams();
		 reset = !reset;
	 }

 }

 inline void PointLight::GetParams()
 {
	 PLight.color = this->color;
	 PLight.Kc = this->Kc / radius * 1.6f;
	 PLight.Kl = this->Kl / radius * 1.6f;
	 PLight.Kq = this->Kq / radius * 1.6f;
	 PLight.position = this->transform->_position;
	 PLight.strengh = this->strengh;
 }


 class DirectionalLight : public Light
 {
 private:
	 int id;
 public:
	 DirectionalLight(vec3);
	 ~DirectionalLight();
	 vec3 direction;
	 DirectionalL DLight;
	 void Update();
	 void GetParams();
 };



 DirectionalLight::DirectionalLight(vec3 dir)
 {
	 direction = dir;
	 color = vec3(1);
	 strengh = 1.f;
	 DLight.color = this->color;
	 DLight.direction = this->direction;
	 DLight.strengh = this->strengh;

	 dirLs.insert(dirLs.end(), &DLight);
	 id = dirLs.size() - 1;
 }


 DirectionalLight::~DirectionalLight()
 {
	 dirLs.erase(dirLs.begin() + id);
 }

 inline void DirectionalLight::Update()
 {
	 if (reset)
	 {
		 GetParams();
		 reset = !reset;
	 }
 }

 inline void DirectionalLight::GetParams()
 {
	 DLight.color = this->color;
	 DLight.direction = this->direction;
	 DLight.strengh = this->strengh;
 }
