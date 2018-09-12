#pragma once

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
		vec3 lightCol = vec3(1);
		vec3 objectCol = vec3(1);
		vec3 lightPos = vec3(1);
		float ambient = 0.1f;
		float diffuse = 0.8f;
		float specular = 32.f;
	};
public:
	Params params;
	void ActiveUniforms();
	Shader * shader;
	void Draw();
	void ActiveShader();
	Material(const GLchar*,GLfloat*,GLsizei, GLenum, GLint*, GLint, GLint, GLint, GLint, GLint*, GLsizei );
	void SetUnifVec3(const GLchar*, vec3);
	void SetUnifMat4(const GLchar*, mat4);
	void SetUnifVec2(const GLchar*, vec2);
	void SetUnifFloat(const GLchar*, GLfloat);
	void SetUnifInt(const GLchar*, GLint);
	~Material();
};


void Material::ActiveUniforms()
{
	SetUnifVec2("stretch", params.stretch);
	SetUnifVec2("offset", params.offset);
	SetUnifVec3("Colors.light", params.lightCol);
	SetUnifVec3("Colors.object", params.objectCol);
	SetUnifVec3("Poses.light", params.lightPos);
	SetUnifFloat("Props.ambient", params.ambient);
	SetUnifFloat("Props.diffuse", params.diffuse);
	SetUnifFloat("Props.specular", params.specular);
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

inline void Material::SetUnifVec3(const GLchar * name, vec3 param)
{
	glUniform3f(glGetUniformLocation(shader->Sprogram(), name), param.x, param.y, param.z);
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
