#pragma once
#include "Component.h"

class TestClass : public Component
{
private:
	GameObject * gameObject;
public:
	void Update();
	void myFunc();

	TestClass(GameObject* game) : gameObject(game) {}
	~TestClass() {}
};

void TestClass::myFunc() 
{
	PointLight* var = (PointLight*)gameObject->GetComponent("PLight");
	if (var!=nullptr)
	{
		var->radius = 2;
		var->strengh = sin(Time::currenttime);
		var->color = vec3(1.f, 0.5f, 0.2f)*sin(Time::currenttime);
		var->reset = true;
	}
}

void TestClass::Update() 
{
	myFunc();
}
