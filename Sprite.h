#pragma once
class Sprite : public GameObject
{
private: 
	GLint params[2] = { 2,2 };
	GLfloat quad[24] =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
public:
	vec3 color = vec3(1);
	float transparent = 1;
	Texture2D *texture;
	Sprite();
	Sprite(const GLchar*);
	~Sprite();
	void Draw();
};



Sprite::Sprite()
{
	material = new Material("Default/Sprite", quad, sizeof(quad), GL_STATIC_DRAW, params, GL_FALSE, GL_TRUE, 2, 6);
}

Sprite::Sprite(const GLchar* path)
{
	GameObject::material = new Material("Default/Sprite", quad, sizeof(quad), GL_STATIC_DRAW, params, GL_FALSE, GL_TRUE, 2, 6);
	texture = new Texture2D(path);
}


Sprite::~Sprite()
{
	delete texture;
}

inline void Sprite::Draw()
{
	glDisable(GL_CULL_FACE);

	material->ActiveShader();
	material->SetUnifInt("Textures.main", 0);
	material->SetUnifFloat("transparent", transparent);
	transform->MoveGlobalMatrix();
	material->SetUnifMat4("Matrix.model", Matrix::model);
	material->SetUnifMat4("Matrix.view", Matrix::view);
	material->SetUnifMat4("Matrix.projection", Matrix::projection);
	material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform->_position);
	material->SetUnifVec3("col", color);

	texture->Active();
	material->Draw();

	glEnable(GL_CULL_FACE);
}
