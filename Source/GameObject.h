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
	Model * GetModel() { return model; }
	Material *material;
	Transform *transform = new Transform();
	Mesh* mesh;

	template<typename T>
	void AddComponent()
	{
		Component* component = new T();
		component->setParentGameObject(this);
		component->transform = this->transform;
		component->Awake();
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
	}		
	template<typename T>
	T* AddComponentR()
	{
		Component* component = new T();
		component->setParentGameObject(this);
		component->transform = this->transform;
		component->Awake();
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
		return (T*)component;
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
	void Draw(GLuint);
	void Draw();
	void ComponentAction();
	
	GameObject();
	virtual ~GameObject();
	GameObject(Mesh*,Material*);
	GameObject(string model,Material*);
};



inline void GameObject::Draw(GLuint countDraws)
{	
	if (mesh != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		mesh->DrawInstanced(countDraws, material);

	}
	if (model != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		model->InstanceDraw(countDraws, material);
	}
	ComponentAction();
}

inline void GameObject::Draw()
{
	if (mesh != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		mesh->Draw(material);
	}
	if (model != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		model->Draw(material);
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

inline GameObject::GameObject(Mesh* mesh,Material* _material)
{
	this->mesh = mesh;
	material = _material; 
}

inline GameObject::GameObject(string model, Material* material)
{
	this->material = material;
	this->model = new Model(model.c_str());
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
	delete mesh;
	delete transform;
}
