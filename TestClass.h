#pragma once

class TestClass : public Component
{
private:
public:
	void Update();
	void myFunc();

	TestClass() {}
	~TestClass() {}
};

void TestClass::myFunc() 
{
	gameObject->GetComponent<PointLight>()->radius = Time::deltaTime;
	if (Input::GetKey(GLFW_KEY_UP))
	{
		gameObject->GetComponent<PointLight>()->strengh += Time::deltaTime;
	}
}

void TestClass::Update() 
{
	myFunc();
}
