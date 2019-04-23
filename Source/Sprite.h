#pragma once
class Sprite : public GameObject
{
private: 
	GLuint texture = GL_FALSE;
public:
	vec3 color = vec3(1);
	float transparent = 1;
	Sprite();
	Sprite(GLuint);
	Sprite(const GLchar*);
	~Sprite();
	void Draw();
	void SetTexture(GLuint);
};



Sprite::Sprite()
{
	material = new Material("Default/Sprite");
	mesh = Primitive::Quad();
}

inline Sprite::Sprite(GLuint id)
{
	material = new Material("Default/Sprite");
	mesh = Primitive::Quad();
	material->SetTexture(id, "texture_diffuse");
}

Sprite::Sprite(const GLchar* path)
{
	GameObject::material = new Material("Default/Sprite");
	mesh = Primitive::Quad();
	texture = Texture2D::Texture2D(path);
	material->SetTexture(texture, "texture_diffuse");
}


Sprite::~Sprite()
{
	if (texture != GL_FALSE)
	{
		glDeleteTextures(1, &texture);
	}
}

inline void Sprite::Draw()
{
	glDisable(GL_CULL_FACE);

	material->ActiveShader();
	material->SetUnifFloat("transparent", transparent);
	transform->MoveGlobalMatrix();
	material->SetUnifMat4("Matrix.model", Matrix::model);
	material->SetUnifMat4("Matrix.view", Matrix::view);
	material->SetUnifMat4("Matrix.projection", Matrix::projection);
	material->SetUnifVec3("col", color);

	mesh->Draw(material);

	glEnable(GL_CULL_FACE);
}

inline void Sprite::SetTexture(GLuint id)
{
	material->SetTexture(id, "texture_diffuse");
}