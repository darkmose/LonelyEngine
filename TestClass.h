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
	{

	}
}

void TestClass::Update() 
{
	myFunc();
}
