#pragma once

class Texture2D
{
private:

	GLuint texture;

public:

	static void FilterTextures(GLint);	

	GLuint Texture();
	void Active(GLenum);
	Texture2D(const GLchar*, GLenum, GLint, GLint);
	~Texture2D();
};

void Texture2D::FilterTextures(GLint filterMod)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMod);
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

Texture2D::Texture2D(const GLchar* path, GLenum soilRGB, GLint RGBStore, GLint RGBSource)
{
	glGenTextures(1, &texture);

	int w, h;
	unsigned char* image = SOIL_load_image(path, &w, &h, 0, soilRGB);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, RGBStore, w, h, 0, RGBSource, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);	
}


Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture);
}
