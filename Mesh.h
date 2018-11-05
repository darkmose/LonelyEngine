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
	Mesh(const VertexVec&, vector<GLuint>, GLenum);
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

inline Mesh::Mesh(const VertexVec& verts, vector<GLuint> ind = vector<GLuint>::vector(), GLenum drawMod = GL_STATIC_DRAW)
{
	char p=0, n=0, t=0;

	if (ind.size() != 0) {
		indices = ind;
		isArray = GL_FALSE;
	}
	
	vertCount = sizeof(verts.pos) / sizeof(GLfloat);
	
	if (sizeof(verts.pos) == 4)	
		p = 0;
	else
		p = 1;	
	if (sizeof(verts.normal) == 4)	
		n = 0;
	else
		n = 1;	
	if (sizeof(verts.texCoords) == 4)	
		t = 0;
	else
		t = 1;

	
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts.pos), &verts.pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts.pos), sizeof(verts.normal), &verts.normal);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts.pos) + sizeof(verts.normal), sizeof(verts.texCoords), &verts.texCoords);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, p*3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, n*3 * sizeof(float), (void*)(sizeof(verts.pos)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, t*2 * sizeof(float), (void*)(sizeof(verts.pos) + sizeof(verts.normal)));
	if (ind.size() != 0)
	{
		GLuint* _data = &ind[0];
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size()*sizeof(GLuint), _data, drawMod);
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
