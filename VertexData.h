#pragma once

class VertexData
{
private:
	GLuint VbO, VaO, EbO;
	mat4 modelMatrix;
	GLint vertCount;
	GLint isArray;
	Shader* shader;
	
public:
	void Draw();
	GLuint VAO();
	void SetModel(mat4 model);
	mat4 GetModel();
	VertexData(const GLchar*,GLfloat*,GLsizei, GLenum, GLint*, GLint, GLint, GLint, GLint,bool, GLint*, GLsizei );
	~VertexData();
	
	GLuint sProgram();

	//Object* parentObj = nullptr;
};



VertexData::VertexData(const GLchar* _shader,GLfloat* vertexArray, GLsizei sizeArray, GLenum drawMod, GLint* params, GLint isNDC, GLint drawArrays, GLint paramCount, GLint _vertCount, bool uniforms, GLint* indices = 0, GLsizei sizeElem = 0) 
{
		shader = new Shader(_shader);
		shader->SetUniforms(uniforms);
		shader->Light = vec3(1, 0.5, 1);
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

GLuint VertexData::VAO() 
{
	return VaO;
}

void VertexData::SetModel(mat4 model)
{
	modelMatrix = model;
}

mat4 VertexData::GetModel()
{
	return modelMatrix;
}


VertexData::~VertexData()
{
	glBindVertexArray(0);
	glDeleteBuffers(1,&VaO);
	glDeleteBuffers(1,&VbO);
	if (isArray == GL_FALSE)
	{
		glDeleteBuffers(1, &EbO);
	}
}

inline GLuint VertexData::sProgram()
{
	return shader->Sprogram();
}

void VertexData::Draw() 
{
	shader->Active();
	shader->ActiveUniforms();
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