#pragma once
#include "Component.h"
#include "Light.h"

class GameObject
{
private:	
	GLboolean isEmpty;
	map<string, Component*> components;
	Model *model;
public:
	Material * material;
	Transform transform;
	void AddComponent(string, Component*);
	Component* GetComponent(string);
	void Draw();
	void ComponentAction();
	GameObject();
	~GameObject();
	GameObject(Material*);
	GameObject(Material*,const GLchar*);
};



inline void GameObject::AddComponent(string name, Component *component)
{
	components[name] = component;
}

inline Component * GameObject::GetComponent(string name)
{
	return components[name];
}

inline void GameObject::Draw()
{
	if (isEmpty)
	{

	}
	else
	{
		material->ActiveShader();
		transform.MoveGlobalMatrix();
		material->SetUnifMat4("Matrix.model", Matrix::model);
		material->SetUnifMat4("Matrix.view", Matrix::view);
		material->SetUnifMat4("Matrix.projection", Matrix::projection);
		material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform._position);
		model->Draw();
	}
	ComponentAction();
}

inline void GameObject::ComponentAction()
{
	map <string, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it).second->Update();
	}
}

inline GameObject::GameObject(Material* _material)
{
	Texture2D box("Textures/metal.jpg", SOIL_LOAD_RGB, GL_RGB, GL_RGB);
	box.Active();
	material = _material;
	model = new Model("Models/cube/untitled.obj", *material);	
}

inline GameObject::GameObject(Material * mat, const GLchar * modelPath)
{
	material = mat;
	model = new Model(modelPath, *material);
}

inline GameObject::GameObject()
{
	isEmpty = true;
}

inline GameObject::~GameObject()
{
	components.clear();
	delete[] model;
}
