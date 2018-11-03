#pragma once
#include "Light.h"
#include "Shader.h"

class Material
{
private:
	struct Params {
		vec2 stretch = vec2(1);
		vec2 offset = vec2(0);
		vec3 objectCol = vec3(1);
		float ambient = 0.1f;
		float diffuse = 0.8f;
		float specular = 0.3f;
		float specularStr = 32.f;
	};
public:
	Params params;
	void ActiveUniforms();
	Shader * shader;
	void ActiveShader();
	void ActiveLight();
	Material(const GLchar*);
	vector<Texture> textures;
	void SetSingleTexture(Texture2D*, string);
	void AddTexture(Texture2D*, string);

	void SetUnifVec3(const GLchar*, vec3);
	void SetUnifVec4(const GLchar*, vec4);
	void SetUnifMat4(const GLchar*, mat4);
	void SetUnifVec2(const GLchar*, vec2);
	void SetUnifFloat(const GLchar*, GLfloat);
	void SetUnifInt(const GLchar*, GLint);
	~Material();
};

void Material::ActiveLight() 
{
	for (size_t i = 0; i < Light::pointLs.size(); i++)
	{
		char* intValue = new char[2];
		_itoa_s(i, intValue, 2, 10);
		string Kc = "Point[" + string(intValue) + "].Kc";
		string Kl = "Point[" + string(intValue) + "].Kl";
		string Kq = "Point[" + string(intValue) + "].Kq";
		string str = "Point[" + string(intValue) + "].strengh";
		string col = "Point[" + string(intValue) + "].color";
		string pos = "Point[" + string(intValue) + "].position";

		SetUnifFloat(Kc.c_str(), (*Light::pointLs[i]).Kc);
		SetUnifFloat(Kl.c_str(), (*Light::pointLs[i]).Kl);
		SetUnifFloat(Kq.c_str(), (*Light::pointLs[i]).Kq);
		SetUnifFloat(str.c_str(), (*Light::pointLs[i]).strengh);
		SetUnifVec3(col.c_str(), (*Light::pointLs[i]).color);
		SetUnifVec3(pos.c_str(), (*Light::pointLs[i]).position);
	}
	for (size_t i = 0; i < Light::spotLs.size(); i++)
	{
		char* intValue = new char[2];
		_itoa_s(i, intValue, 2, 10);
		string pos = "Spot[" + string(intValue) + "].position";
		string dir = "Spot[" + string(intValue) + "].direction";
		string Icutoff = "Spot[" + string(intValue) + "].innerCutOff";
		string Ocutoff = "Spot[" + string(intValue) + "].outerCutOff";
		string str = "Spot[" + string(intValue) + "].color";
		string colr = "Spot[" + string(intValue) + "].position";

		SetUnifVec3(pos.c_str(), Camera::mainCamera->transform->_position);
		SetUnifVec3(dir.c_str(), Camera::mainCamera->Direction());
		SetUnifFloat(Icutoff.c_str(), (*Light::spotLs[i]).innerCutOff);
		SetUnifFloat(Ocutoff.c_str(), (*Light::spotLs[i]).outerCutOff);
		SetUnifFloat(str.c_str(), (*Light::spotLs[i]).strengh);
		SetUnifVec3(colr.c_str(), (*Light::spotLs[i]).color);
	}
	for (size_t i = 0; i < Light::dirLs.size(); i++)
	{
		char* intValue = new char[2];
		_itoa_s(i, intValue, 2, 10);

		string dir = "Directional[" + string(intValue) + "].direction";
		string col = "Directional[" + string(intValue) + "].color";
		string str = "Directional[" + string(intValue) + "].strengh";

		SetUnifVec3(dir.c_str(), (*Light::dirLs[i]).direction);
		SetUnifVec3(col.c_str(), (*Light::dirLs[i]).color);
		SetUnifFloat(str.c_str(), (*Light::dirLs[i]).strengh);
	}
}

void Material::ActiveUniforms()
{
	SetUnifVec2("stretch", params.stretch);
	SetUnifVec2("offset", params.offset);
	SetUnifVec3("Props.objectColor", params.objectCol);
	SetUnifVec3("cameraPos", Camera::mainCamera->transform->_position);
	SetUnifFloat("Props.ambient", params.ambient);
	SetUnifFloat("Props.diffuse", params.diffuse);
	SetUnifFloat("Props.specularStr", params.specularStr);
	SetUnifFloat("Props.specular", params.specular);
}

inline Material::Material(const GLchar * sh)
{
	shader = new Shader(sh);
}

inline void Material::SetSingleTexture(Texture2D* tex, string textureType)
{
	textures.clear();
	Texture texture;
	texture.id = tex->Texture();
	texture.type = textureType;
	textures.push_back(texture);
}

inline void Material::AddTexture(Texture2D * tex, string textureType)
{
	Texture texture;
	texture.id = tex->Texture();
	texture.type = textureType;
	textures.push_back(texture);
}

inline void Material::SetUnifVec3(const GLchar * name, vec3 param)
{
	glUniform3f(glGetUniformLocation(shader->Sprogram(), name), param.x, param.y, param.z);
}

inline void Material::SetUnifVec4(const GLchar * name, vec4 param)
{
	glUniform4f(glGetUniformLocation(shader->Sprogram(), name), param.x, param.y, param.z,param.w);
}

inline void Material::SetUnifMat4(const GLchar * name, mat4 param)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->Sprogram(), name), 1, GL_FALSE, value_ptr(param));
}

inline void Material::SetUnifVec2(const GLchar *name, vec2 param)
{
	glUniform2f(glGetUniformLocation(shader->Sprogram(), name), param.x, param.y);
}

inline void Material::SetUnifFloat(const GLchar * name, GLfloat param)
{
	glUniform1f(glGetUniformLocation(shader->Sprogram(), name), param);
}

inline void Material::SetUnifInt(const GLchar * name, GLint param)
{
	glUniform1i(glGetUniformLocation(shader->Sprogram(), name), param);
}

Material::~Material()
{	
	textures.clear();
}

inline void Material::ActiveShader()
{
	shader->Active();
}
