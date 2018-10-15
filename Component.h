#pragma once

class Component
{
public:
	bool reset = true;
	virtual void Update() {}
	void setParentGameObject(GameObject*);
	Component() {}
	virtual void Awake() {}
	virtual ~Component() {}

protected:
	GameObject * gameObject = NULL;
};

void Component::setParentGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}
