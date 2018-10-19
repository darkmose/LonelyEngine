#pragma once 

class test : public Component
{
private:
	void Awake() 
	{
		cout << "HUI";
	}

	void Update() 
	{		
		gameObject->GetComponent<PointLight>()->color += vec3(0.001f, Time::deltaTime, 0);
	}
public:
	virtual ~test() {}
	test() {}
};