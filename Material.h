#pragma once
#include "Light.h"
#include "Camera.h"

class Material
{
private:
	GLuint VbO, VaO, EbO;
	mat4 modelMatrix;
	GLint vertCount;
	GLint isArray;
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
	void ActiveTextures();
	Shader * shader;
	void Draw();
	void ActiveShader();
	void ActiveLight();
	Material(const GLchar*,GLfloat*,GLsizei, GLenum, GLint*, GLint, GLint, GLint, GLint, GLint*, GLsizei );
	Material(const GLchar*);
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

		SetUnifVec3(pos.c_str(), Camera::mainCamera->transform._position);
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
	SetUnifVec3("cameraPos", Camera::mainCamera->transform._position);
	SetUnifFloat("Props.ambient", params.ambient);
	SetUnifFloat("Props.diffuse", params.diffuse);
	SetUnifFloat("Props.specularStr", params.specularStr);
	SetUnifFloat("Props.specular", params.specular);
}

inline void Material::ActiveTextures()
{
	SetUnifInt("Textures.main", 0);
}




Material::Material(const GLchar* _shader,GLfloat* vertexArray, GLsizei sizeArray, GLenum drawMod, GLint* params, GLint isNDC, GLint drawArrays, GLint paramCount, GLint _vertCount, GLint* indices = 0, GLsizei sizeElem = 0)
{
		shader = new Shader(_shader);
		vertCount = _vertCount;
		isArray = drawArrays;
		glGenVertexArrays(1, &VaO);
		glBindVertexArray(VaO);
		glGenBuffers(1, &VbO);
		glBindBuffer(GL_ARRAY_BUFFER, VbO);
		glBufferData(GL_ARRAY_BUFFER, sizeArray, vertexArray, drawMod);
		if (drawArrays == GL_FALSE)
		{
			glGenBuffers(1, &EbO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EbO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeElem, indices, drawMod);
		}


		GLint elemCount = 0;

		for (GLint i = 0; i < paramCount; i++)
		{
			elemCount += params[i];
		}

		GLsizei size = elemCount * sizeof(float);

		GLint prev = 0;
		for (GLint i = 0; i < paramCount; i++)
		{
			glVertexAttribPointer(i, params[i], GL_FLOAT, isNDC, size, (GLvoid*)(prev * sizeof(float)));
			prev += params[i];
			glEnableVertexAttribArray(i);
		}
		glBindVertexArray(0);
	
	
}

inline Material::Material(const GLchar * sh)
{
	shader = new Shader(sh);
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
	glBindVertexArray(0);
	glDeleteBuffers(1,&VaO);
	glDeleteBuffers(1,&VbO);
	if (isArray == GL_FALSE)
	{
		glDeleteBuffers(1, &EbO);
	}
}


void Material::Draw()
{
	if (isArray == GL_FALSE)
	{
		glBindVertexArray(VaO);
		glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, 0);
		
		return;
	}
	else
	{	
		glBindVertexArray(VaO);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		
		return;
	}	
}

inline void Material::ActiveShader()
{
	shader->Active();
}
