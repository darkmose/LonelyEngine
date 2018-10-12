#pragma once
#include "Component.h"
#include "Light.h"

class GameObject
{
private:	
	GLboolean isEmpty, isModel;
	map<void*, Component*> components;
	Model *model;
public:
	Material * material;
	Transform transform;

	template<typename T>
	void AddComponent(Component* component)
	{
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(std::pair<void*, Component*>(ptr, component));
	}
	template<typename T>
	T* GetComponent() 
	{
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		return (T*)components[ptr];
	}
	void Draw();
	void ComponentAction();
	GameObject();
	~GameObject();
	GameObject(Material*);
	GameObject(string model,Material&);
};



inline void GameObject::Draw()
{
	
	if (!isEmpty)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		material->ActiveTextures();
		material->ActiveLight();
		transform.MoveGlobalMatrix();
		material->SetUnifMat4("Matrix.model", Matrix::model);
		material->SetUnifMat4("Matrix.view", Matrix::view);
		material->SetUnifMat4("Matrix.projection", Matrix::projection);
		material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform._position);

		material->Draw();
	}
	if (isModel)
	{
		material->ActiveShader();
		material->ActiveLight();
		material->ActiveUniforms();
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
	map <void*, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it).second->Update();
	}
}

inline GameObject::GameObject(Material* _material)
{
	material = _material; 
}

inline GameObject::GameObject(string model, Material& material)
{
	this->material = &material;
	this->model = new Model(model.c_str(), *this->material);
	isEmpty = true;
	isModel = true;
}

inline GameObject::GameObject()
{
	isEmpty = true;
}

inline GameObject::~GameObject()
{
	components.clear();
}
