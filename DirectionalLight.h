#pragma once
#include "Light.h"


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
	GetParams();
}

inline void DirectionalLight::GetParams()
{
	DLight.color = this->color;
	DLight.direction = this->direction;
	DLight.strengh = this->strengh;
}
