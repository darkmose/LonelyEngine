#pragma once

class GameObj 
{
private:	
public:
	Material * material;
	Transform transform;
	void Draw();
	GameObj(Material*, vec3&, vec3&);
	GameObj(Material*);
	vec3 LightPos;
	void SetLightPos(vec3);
};



inline void GameObj::Draw()
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



GameObj::GameObj(Material* material, vec3& _light, vec3& lPos) : material(material)
{
	material->params.lightCol = _light;
	SetLightPos(lPos);
}

GameObj::GameObj(Material* material) : material(material){}

inline void GameObj::SetLightPos(vec3 pos)
{
	material->params.lightPos = pos;
}
