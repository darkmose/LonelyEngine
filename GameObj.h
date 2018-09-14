#pragma once

class GameObj 
{
private:	
	GLboolean isEmpty;
	map<string, Component*> components;
public:
	Material * material;
	Transform transform;
	void AddComponent(string, Component*);
	Component* GetComponent(string);
	void Draw();
	void ComponentAction();
	GameObj();
	GameObj(Material*);
};



inline void GameObj::AddComponent(string name, Component *component)
{
	components[name] = component;
}

inline Component * GameObj::GetComponent(string name)
{
	return components[name];
}

inline void GameObj::Draw()
{
	if (!isEmpty)
	{
		material->ActiveShader();
		material->ActiveUniforms();
		transform.MoveGlobalMatrix();
		material->SetUnifMat4("Matrix.model", Matrix::model);
		material->SetUnifMat4("Matrix.view", Matrix::view);
		material->SetUnifMat4("Matrix.projection", Matrix::projection);
		material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform._position);

		material->Draw();
	}
	ComponentAction();
}

inline void GameObj::ComponentAction()
{
	map <string, Component*>::iterator it;
	for (it = components.begin(); it != components.end(); ++it)
	{
		(*it).second->Action();
	}
}

inline GameObj::GameObj(Material* _material)
{
	material = _material; 
}

inline GameObj::GameObj()
{
	isEmpty = true;
}
