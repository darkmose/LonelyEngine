#pragma once

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};
struct Texture
{
	string type;
	GLuint id;
	aiString path;
};

class Mesh
{

public:
	GLuint VAO, VBO, EBO;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	void SetupMesh();
	void Draw(Material&);

	Mesh(vector<Vertex>, vector<unsigned int>, vector<Texture>);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal));
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
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

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->textures = textures;
	this->indices = indices;
	this->vertices = vertices;

		SetupMesh();
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
