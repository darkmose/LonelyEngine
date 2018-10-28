#pragma once
class Sprite : public GameObject
{
private: 
	vector<GLint> params = { 2,2 };
	vector<GLfloat> quad =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	Texture2D *texture;

public:
	vec3 color = vec3(1);
	float transparent = 1;
	Sprite();
	Sprite(const GLchar*);
	~Sprite();
	void Draw();
	void SetTexture(Texture2D*);
};



Sprite::Sprite()
{
	material = new Material("Default/Sprite");
	mesh = new Mesh(quad, vector<GLuint>::vector(), params);
}

Sprite::Sprite(const GLchar* path)
{
	GameObject::material = new Material("Default/Sprite");
	mesh = new Mesh(quad, vector<GLuint>::vector(), params);
	texture = new Texture2D(path);
	material->SetSingleTexture(texture, "texture_diffuse");
}


Sprite::~Sprite()
{
	delete texture;
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
	material->SetUnifVec3("Poses.camera", Camera::mainCamera->transform->_position);
	material->SetUnifVec3("col", color);

	texture->Active();
	mesh->Draw(material,true);

	glEnable(GL_CULL_FACE);
}

inline void Sprite::SetTexture(Texture2D * tex)
{
	texture = tex;
	material->SetSingleTexture(texture, "texture_diffuse");
}
