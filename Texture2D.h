#pragma once
class Texture2D
{
private:

	GLuint texture;

public:

	static void FilterTextures(GLint);	

	GLuint Texture();


	Texture2D(GLchar*, GLenum, GLint, GLint, GLenum);
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

Texture2D::Texture2D(GLchar* path,GLenum soilRGB, GLint RGBStore, GLint RGBSource, GLenum activeTexture)
{
	glGenTextures(1, &texture);
	
	int w, h;
	unsigned char* image = SOIL_load_image(path, &w, &h, 0, soilRGB);

	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, RGBStore, w, h, 0, RGBSource, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);	
}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &texture);
}
