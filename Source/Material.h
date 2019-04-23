#pragma once
#include "Light.h"
#include "Shader.h"
#include "RenderTexture.h"

class Material
{
private:
	struct Params
	{
		vec2 stretch = vec2(1);
		vec2 offset = vec2(0);
		vec3 objectCol = vec3(1);
	};
	struct MatProps
	{
		float ambient = 0.1f;
		float diffuse = 0.8f;
		float specular = 0.3f;
		float specularStr = 32.f;
	};
public:
	Params params;
	MatProps matProps;
	void ActiveUniforms();
	Shader * shader;
	void ActiveShader();
	Material(const GLchar*);
	vector<Texture> textures;
	void SetTexture(GLuint, string);
	void AddTexture(GLuint, string);
	void SetUnifVec3(const GLchar*, vec3);
	void SetUnifVec4(const GLchar*, vec4);
	void SetUnifMat4(const GLchar*, mat4);
	void SetUnifVec2(const GLchar*, vec2);
	void SetUnifFloat(const GLchar*, GLfloat);
	void SetUnifInt(const GLchar*, GLint);
	~Material();
	void BindUniformBuffer(const GLchar*, GLuint);
};

void Material::ActiveUniforms()
{
	SetUnifVec2("stretch", params.stretch);
	SetUnifVec2("offset", params.offset);
	SetUnifVec3("objColor", params.objectCol);
}

inline Material::Material(const GLchar * sh)
{
	shader = new Shader(sh);
}

inline void Material::SetTexture(GLuint id, string textureType)
{
	textures.clear();
	Texture texture;
	texture.id = id;
	texture.type = textureType;
	textures.push_back(texture);
}

inline void Material::AddTexture(GLuint id, string textureType)
{
	Texture texture;
	texture.id = id;
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

inline void Material::BindUniformBuffer(const GLchar * unifName, GLuint idBlock)
{
	GLuint idUnifBlock = glGetUniformBlockIndex(shader->Sprogram(), unifName);
	glUniformBlockBinding(shader->Sprogram(), idUnifBlock, idBlock);
}

inline void Material::ActiveShader()
{
	shader->Active();
}
