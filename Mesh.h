#pragma once

class Mesh
{
private:
	GLint vertCount;
	GLint isArray = GL_TRUE;
	GLuint VAO, VBO, EBO;
public:
	Material * material;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	void SetupMesh();
	void Draw(Material&);
	void Draw(Material*, bool);
	
	Mesh(vector<Vertex>, vector<unsigned int>, vector<Texture>);
	Mesh(vector<GLfloat>, vector<GLuint>, vector<GLint>, GLenum);
	~Mesh();
};


inline void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,TexCoords));
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

inline void Mesh::Draw(Material& materialRef)
{
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
		else if(name == "texture_specular")
		{
			ss << specularNr++;
		}
		number = ss.str();

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		materialRef.SetUnifInt(("Textures." + name + number).c_str(), i);		
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);		
}

inline void Mesh::Draw(Material* mater,bool isNotModel)
{
	textures = mater->textures;
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
		mater->SetUnifInt(("Textures." + name + number).c_str(), i);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);

	if (isArray == GL_FALSE)
		glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertCount);

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->textures = textures;
	this->indices = indices;
	this->vertices = vertices;

		SetupMesh();
}

inline Mesh::Mesh(vector<GLfloat> vert, vector<GLuint> ind, vector<GLint> params, GLenum drawMod = GL_STATIC_DRAW)
{

	if (ind.size() != 0) {
		indices = ind;
		isArray = GL_FALSE;
	}

	int shag = 0;
	for(int i = 0; i<params.size();i++)
		shag += params[i];

	vertCount = int(vert.size() / shag);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLfloat* data = &vert[0];
	glBufferData(GL_ARRAY_BUFFER, vert.size()*sizeof(GLfloat), data, drawMod);

	if (ind.size() != 0)
	{
		GLuint* _data = &ind[0];
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size()*sizeof(GLuint), _data, drawMod);
	}

	GLint prev = 0;
	for (GLint i = 0; i < params.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, params[i], GL_FLOAT, GL_FALSE, shag*sizeof(GLfloat), (GLvoid*)(prev * sizeof(float)));
		prev += params[i];
	}
	glBindVertexArray(0);	
}


Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
	textures.clear();
	glBindVertexArray(0);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
