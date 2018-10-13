#pragma once

class Component
{
public:
	bool reset = true;
	virtual void Update() {}
	void setParentGameObject(GameObject*);
protected:
	GameObject *gameObject;
};

void Component::setParentGameObject(GameObject* gameObject)
{
	this->gameObject = gameObject;
}
