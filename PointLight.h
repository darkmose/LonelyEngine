#pragma once
#include "Light.h"

class PointLight :	public Light
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
	PLight.Kl = this->Kl /radius * 1.6f;
	PLight.Kq = this->Kq /radius * 1.6f;
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
	GetParams();
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
