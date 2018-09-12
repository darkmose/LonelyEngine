#pragma once

class Light
{
private:
	Material * material;
	vec3* lPoss;
public:
	Transform transform;
	void Draw();
	Light(vec3&);
	void SetLightColor(vec3&,vec3);
	void SetLPos(vec3);
	~Light();
};

void Light::SetLPos(vec3 pos) 
{
	transform._position += pos;
	*lPoss = transform._position;	
}

inline Light::~Light()
{
	delete[] material;
}

inline void Light::SetLightColor(vec3& global, vec3 color)
{
	global = color;
}

inline void Light::Draw()
{
	material->ActiveShader();
	transform.MoveGlobalMatrix();
	material->SetUnifMat4("Matrix.model", Matrix::model);
	material->SetUnifMat4("Matrix.view", Matrix::view);
	material->SetUnifMat4("Matrix.projection", Matrix::projection);
	material->Draw();
}

Light::Light(vec3& lPos)
{
	lPoss = &lPos;
	GLint lightParam[] = { 3 };
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	material = new Material("Default/Light", vertices, sizeof(vertices), GL_STATIC_DRAW, lightParam, GL_FALSE, GL_TRUE, 1, 36);
	transform._position = vec3(2, 5, 3);
	lPos = transform._position;
}

