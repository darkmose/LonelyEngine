#pragma once

class Texture2D
{
private:
	GLuint texture;
public:
	static GLuint TexFromPath(const GLchar* path);
	static void FilterTextures(GLint, GLint);
	GLuint Texture();
	void Active(GLenum);
	Texture2D(const GLchar*);
	Texture2D(vector<std::string>);
	~Texture2D();
};

GLuint Texture2D::TexFromPath(const GLchar * path)
{
	GLuint tex;

	glGenTextures(1, &tex);

	int w, h, ch;
	unsigned char* image = SOIL_load_image(path, &w, &h, &ch, SOIL_LOAD_AUTO);

	if (image == NULL)
	{
		SOIL_free_image_data(image);
		return 0;
	}
	GLint rgba;

	switch (ch)
	{
	case 1:
		rgba = GL_RED;
		break;
	case 2:
		rgba = GL_RG;
		break;
	case 3:
		rgba = GL_RGB;
		break;
	case 4:
		rgba = GL_RGBA;
		break;
	}
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, rgba, w, h, 0, rgba, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

void Texture2D::FilterTextures(GLint wrap, GLint filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

Texture2D::Texture2D(vector<string> faces)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, ch;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &ch, SOIL_LOAD_AUTO);
		
		GLint rgba;
		switch (ch)
		{
		case 1:
			rgba = GL_RED;
			break;
		case 2:
			rgba = GL_RG;
			break;
		case 3:
			rgba = GL_RGB;
			break;
		case 4:
			rgba = GL_RGBA;
			break;
		}		
		
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rgba, width, height, 0, rgba, GL_UNSIGNED_BYTE, data);
			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


GLuint Texture2D::Texture() 
{
	return texture;
}

void Texture2D::Active(GLenum activeTexture = GL_TEXTURE0)
{
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
}

Texture2D::Texture2D(const GLchar* path)
{
	glGenTextures(1, &texture);

	int w, h, ch;
	unsigned char* image = SOIL_load_image(path, &w, &h, &ch, SOIL_LOAD_AUTO);

	if (image == NULL)
	{
		SOIL_free_image_data(image);
		return;
	}

	GLint rgba;

	switch (ch)
	{
	case 1:
		rgba = GL_RED;
		break;
	case 2:
		rgba = GL_RG;
		break;
	case 3:
		rgba = GL_RGB;
		break;
	case 4:
		rgba = GL_RGBA;
		break;
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, rgba, w, h, 0, rgba, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

}


Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &texture);	
}
