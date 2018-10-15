#pragma once
#include "Transform.h"
class GameObject; 
#include "Material.h"
#include "Model.h"

class GameObject
{
private:	
	typedef multimap<void*, Component*> mmap;
	typedef mmap::iterator iterator;
	GLboolean isEmpty, isModel;
	mmap components;
	Model *model;
public:
	Material * material;
	Transform *transform = new Transform();

	template<typename T>
	void AddComponent()
	{
		Component* component = new T();
		component->setParentGameObject(this);
		component->Awake();
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
	}	
	template<typename T>
	void AddComponent(Component* component)
	{
		component->setParentGameObject(this);
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
	}
	template<typename T>
	T* GetComponent() 
	{
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		mmap::iterator it = components.lower_bound(tPtr);
		return (T*)((*it).second);

	}	
	template<typename T>
	T** GetComponents() 
	{
		T** tM;
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		pair<iterator, iterator> range;
		range = components.equal_range(ptr);
		tM = new T*[components.count(ptr)];
		int index = 0;
		for (iterator it = range.first; it != range.second; ++it)
		{
			tM[index++] = (T*)((*it).second);
		}
		return tM;
	}
	template<typename T>
	int countComponents()
	{
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		return components.count(ptr);
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
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("Matrix.model", Matrix::model);
		material->SetUnifMat4("Matrix.view", Matrix::view);
		material->SetUnifMat4("Matrix.projection", Matrix::projection);
		material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform->_position);

		material->Draw();
	}
	if (isModel)
	{
		material->ActiveShader();
		material->ActiveLight();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("Matrix.model", Matrix::model);
		material->SetUnifMat4("Matrix.view", Matrix::view);
		material->SetUnifMat4("Matrix.projection", Matrix::projection);
		material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform->_position);

		model->Draw();
	}
	ComponentAction();
}

inline void GameObject::ComponentAction()
{
	mmap::iterator it;
	
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
	mmap::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		delete (*it).second;
	}
	components.clear();
	delete transform;
}
