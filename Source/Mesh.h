#pragma once

class Mesh
{
private:
	GLint maxAttribPointer = 0;
	bool isArrayDraw = true;
	GLuint VAO, VBO, EBO;
	vector<GLuint> IAO;// - instanced array buffers;
public:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	void Draw(Material*);
	void DrawInstanced(GLsizei, Material*);
	
	template<typename T>
	void InstanceArray(void * data, GLint dataCount, GLint paramCount, GLenum paramType)
	{
		GLuint iao;
		glBindVertexArray(VAO);
		glGenBuffers(1, &iao);
		glBindBuffer(GL_ARRAY_BUFFER, iao);
		glBufferData(GL_ARRAY_BUFFER, dataCount*sizeof(T), data, GL_STATIC_DRAW);
		
		GLint countAttrib;
		GLsizeiptr nStride, offset = 0;

		if (sizeof(T) > sizeof(vec4)) {
			countAttrib = int(sizeof(T) / sizeof(vec4));
			nStride = sizeof(vec4);
		}
		else {
			nStride = 4;
			countAttrib = 1;
		}
		for (int i = 1; i <= countAttrib; i++)
		{			
			glEnableVertexAttribArray(maxAttribPointer + i);
			glVertexAttribPointer(maxAttribPointer + i, paramCount, paramType, GL_FALSE, nStride*paramCount, (void*)offset);
			glVertexAttribDivisor(maxAttribPointer + i, 1);
			offset += nStride;
		}

		maxAttribPointer += countAttrib;
		IAO.push_back(iao);
		glBindVertexArray(0);
	}
	
	Mesh(vector<Vertex>&, vector<unsigned int>&, vector<Texture>&);
	~Mesh();
};

inline void Mesh::Draw(Material* material)
{	
	if (textures.size() == 0) textures = material->textures;
	GLuint diffuseNr = 1,
		specularNr = 1;
	string name, number;
	stringstream ss;
	
	for (size_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		name = textures[i].type;
		if (name == "texture_diffuse")
		{
			ss << diffuseNr++;
		}
		else if (name == "texture_specular")
		{
			ss << specularNr++;
		}
		number = ss.str();

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		material->SetUnifInt(("Textures." + name + number).c_str(), i);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);

	if (!isArrayDraw)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

inline void Mesh::DrawInstanced(GLsizei countDraws, Material* material)
{
	if (this->textures.size() == 0)
	{
		textures = material->textures;
	}
	GLuint diffuseNr = 1,
		specularNr = 1;
	string name, number;
	stringstream ss;

	for (size_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		name = textures[i].type;
		if (name == "texture_diffuse")
		{
			ss << diffuseNr++;
		}
		else if (name == "texture_specular")
		{
			ss << specularNr++;
		}
		number = ss.str();

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		material->SetUnifInt(("Textures." + name + number).c_str(), i);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	if (!isArrayDraw)
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, countDraws);
	else
		glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), countDraws);

}



Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	if (indices.size() != 0)
	{
		isArrayDraw = false;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	maxAttribPointer = 2;
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	for (size_t i = 0; i < IAO.size(); i++)
	{
		glDeleteBuffers(1, &IAO[i]);
	}
	vertices.clear();
	indices.clear();
	textures.clear();
	glBindVertexArray(0);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
