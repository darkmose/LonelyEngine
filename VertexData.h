#pragma once
class VertexData
{
private:
	GLuint VbO, VaO, EbO;
	mat4 modelMatrix;
public:

	GLuint VAO();
	VertexData(GLfloat*, GLint*, GLenum, GLint*, GLint);
	~VertexData();
};



VertexData::VertexData(GLfloat* vertexArray, GLint* indices, GLenum drawMod, GLint* params, GLint isNDC)
{
	glGenBuffers(1, &VaO);
	glBindVertexArray(VaO);
	glGenBuffers(1, &VbO);
	glBindBuffer(GL_ARRAY_BUFFER, VbO);
	glBufferData(GL_ARRAY_BUFFER, 1, vertexArray, drawMod);
	glGenBuffers(1, &EbO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EbO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1, indices, drawMod);
	
	GLint MaxIndex = sizeof(params) / sizeof(GLfloat);
	GLint elemCount;

	for (GLint i = 0; i < MaxIndex; i++)
	{
		elemCount += params[i];
	}

	GLsizei size = elemCount * sizeof(float);

	GLint prev = 0;
	for (GLint i = 0; i < MaxIndex; i++)
	{
		glVertexAttribPointer(i, params[i], GL_FLOAT, isNDC, size, (GLvoid*)(prev*sizeof(float)));
		prev += params[i];
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
}

GLuint VertexData::VAO() 
{
	return VaO;
}

VertexData::~VertexData()
{
	glDeleteBuffers(1,&VaO);
	glDeleteBuffers(1,&VbO);
	glDeleteBuffers(1,&EbO);
}
