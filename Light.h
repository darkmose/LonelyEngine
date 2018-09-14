#pragma once
#include "Component.h"
#include "Transform.h"

class Light : public Component
{
private:
	Transform * trans;
	vec3 tempColor;

public:
	vec3 Color = vec3(1);
	float str = 1;


	static float strengh;
	static vec3 Lcolor;
	static vec3 Lpos;

	virtual void Update();
	Transform transform;
	Light(Transform&);
	~Light();
};


inline void Light::Update()
{
	Light::Lcolor = Color;
	Light::Lpos = trans->_position;
	Light::strengh = str;		
}

inline Light::Light(Transform& _trans)
{
	trans = &_trans;
	Light::Lcolor = Color;
	Light::Lpos = trans->_position;
	Light::strengh = str;
}

inline Light::~Light()
{
	delete[] trans;
}

vec3 Light::Lcolor;
vec3 Light::Lpos;
float Light::strengh;

