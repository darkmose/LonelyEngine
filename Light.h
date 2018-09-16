#pragma once
#include "Component.h"
#include "Transform.h"
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

