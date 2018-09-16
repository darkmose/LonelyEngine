#pragma once
#include "Light.h"
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
	GetParams();
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
