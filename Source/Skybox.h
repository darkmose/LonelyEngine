#pragma once
class Skybox
{
private: 
	GLuint sky;
	const vector<GLfloat> box = {

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	GLuint vbo, vao;
	Shader *shader;
public:
	Skybox(vector<string>);
	Skybox() {}
	Skybox(string, string);
	~Skybox();
	void Draw();
	GLuint CubeMap();
	void BindUniformBuffer(const GLchar * unifName, GLuint idBlock)
	{
		GLuint idUnifBlock = glGetUniformBlockIndex(shader->Sprogram(), unifName);
		glUniformBlockBinding(shader->Sprogram(), idUnifBlock, idBlock);
	}
};

Skybox::Skybox(vector<string> paths)
{
	sky = Texture2D::TextureCube(paths);
	shader = new Shader("Default/Skybox");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(GLfloat), &box[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glBindVertexArray(0);
}



inline Skybox::Skybox(string path, string format)
{
	vector<string> paths;
	paths.push_back(path + "_rt." + format);
	paths.push_back(path + "_lf." + format);
	paths.push_back(path + "_up." + format);
	paths.push_back(path + "_dn." + format);
	paths.push_back(path + "_bk." + format);
	paths.push_back(path + "_ft." + format);

	sky = Texture2D::TextureCube(paths);
	shader = new Shader("Default/Skybox");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, box.size() * sizeof(GLfloat), &box[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glBindVertexArray(0);
}

Skybox::~Skybox()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	delete shader;
}

inline void Skybox::Draw()
{
	glDepthFunc(GL_LEQUAL);
	
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky);

	shader->Active();

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

inline GLuint Skybox::CubeMap()
{
	return sky;
}
