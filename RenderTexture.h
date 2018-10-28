#pragma once
class RenderTexture
{
private:
	GLuint texture;
	GLuint frameBuffer;
	GLuint rbo;
public:
	RenderTexture(int,int,GLenum,GLenum,GLenum,GLenum);
	~RenderTexture();
	void Active(GLenum);
	void ActiveBuffer();
	void DeactiveBuffer();
	GLuint Texture();	
};



RenderTexture::RenderTexture(int w, int h, GLenum frameTarget, GLenum attachment, GLenum formatTexture = GL_RGB, GLenum typeTextureData = GL_UNSIGNED_BYTE)
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, formatTexture, w, h, 0, formatTexture, typeTextureData, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(frameTarget, attachment, GL_TEXTURE_2D, texture, 0);
	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline void RenderTexture::Active(GLenum activeTexture = GL_TEXTURE0)
{
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
}

inline void RenderTexture::ActiveBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

inline void RenderTexture::DeactiveBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline GLuint RenderTexture::Texture()
{
	return texture;
}

RenderTexture::~RenderTexture() 
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &texture);
}