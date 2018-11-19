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
		component->Awake();
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
	}	
	template<typename T>
	void AddComponent(Component* component)
	{
		component->setParentGameObject(this);
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
		component->Awake();
		T* tPtr = NULL;
		void* ptr = dynamic_cast<void*>(tPtr);
		components.insert(mmap::value_type(ptr, component));
		return (T*)component;
	}	
	template<typename T>
	T* AddComponentR(Component* component)
	{
		component->setParentGameObject(this);
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
	void Draw(Material*);
	void Draw();
	void ComponentAction();
	
	GameObject();
	virtual ~GameObject();
	GameObject(Material*, Mesh*);
	GameObject(string model,Material*);
};



inline void GameObject::Draw(GLuint countDraws)
{	
	if (mesh != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		material->ActiveLight();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		mesh->DrawInstanced(countDraws, material);

	}
	if (model != NULL)
	{
		material->ActiveShader();
		material->ActiveLight();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		model->InstanceDraw(countDraws);
	}
	ComponentAction();
}

inline void GameObject::Draw(Material * newMaterial)
{
	Material* tempMat = material;
	material = newMaterial;
	if (mesh != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		material->ActiveLight();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		mesh->Draw(material);
	}
	if (model != NULL)
	{
		model->material = material;
		material->ActiveShader();
		material->ActiveLight();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		model->Draw();
		model->material = tempMat;
	}
	ComponentAction();
	material = tempMat;
}

inline void GameObject::Draw()
{
	if (mesh != NULL)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		material->ActiveLight();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
		mesh->Draw(material);
	}
	if (model != NULL)
	{
		material->ActiveShader();
		material->ActiveLight();
		material->ActiveUniforms();
		transform->MoveGlobalMatrix();
		material->SetUnifMat4("model", Matrix::model);
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

inline GameObject::GameObject(Material* _material,Mesh* mesh)
{
	this->mesh = mesh;
	material = _material; 
}

inline GameObject::GameObject(string model, Material* material)
{
	this->material = material;
	this->model = new Model(model.c_str(), *material);
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
