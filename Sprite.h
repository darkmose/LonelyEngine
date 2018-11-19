#pragma once
class Sprite : public GameObject
{
private: 
	Texture2D *texture;
	RenderTexture* rTex;
public:
	vec3 color = vec3(1);
	float transparent = 1;
	Sprite();
	Sprite(const GLchar*);
	~Sprite();
	void Draw();
	void DrawRender();
	void SetTexture(Texture2D*);
	void SetTexture(RenderTexture*);
};



Sprite::Sprite()
{
	material = new Material("Default/Sprite");
	mesh = Primitive::Quad();
}

Sprite::Sprite(const GLchar* path)
{
	GameObject::material = new Material("Default/Sprite");
	mesh = Primitive::Quad();
	texture = new Texture2D(path);
	material->SetSingleTexture(texture, "texture_diffuse");
}


Sprite::~Sprite()
{
}

inline void Sprite::Draw()
{
	glDisable(GL_CULL_FACE);

	material->ActiveShader();
	material->SetUnifFloat("transparent", transparent);
	transform->MoveGlobalMatrix();
	material->SetUnifMat4("Matrix.model", Matrix::model);
	material->SetUnifVec3("col", color);

	texture->Active();
	mesh->Draw(material);

	glEnable(GL_CULL_FACE);
}

inline void Sprite::DrawRender()
{
	glDisable(GL_CULL_FACE);

	material->ActiveShader();
	material->SetUnifFloat("transparent", 1);
	transform->MoveGlobalMatrix();
	material->SetUnifMat4("Matrix.model", Matrix::model);
	material->SetUnifVec3("col", color);

	mesh->Draw(material);

	glEnable(GL_CULL_FACE);
}

inline void Sprite::SetTexture(Texture2D * tex)
{
	texture = tex;
	material->SetSingleTexture(texture, "texture_diffuse");
}

inline void Sprite::SetTexture(RenderTexture *rTexture)
{
	rTex = rTexture;
	material->SetSingleTexture(rTex, "texture_diffuse");
}
