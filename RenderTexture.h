#pragma once
class RenderTexture
{
private:
	GLuint texture;
	GLuint frameBuffer;
	GLuint rbo;
public:
	RenderTexture(int,int,GLenum,GLenum,GLenum,GLenum,GLenum,GLenum);
	~RenderTexture();
	void Active(int);
	void ActiveBuffer();
	void DeactiveBuffer();
	GLuint BufferObject();
	GLuint Texture();	
};



RenderTexture::RenderTexture(int w, int h, GLenum frameTarget, GLenum frameAttach, GLenum formatTexture = GL_RGB, GLenum typeTextureData = GL_UNSIGNED_BYTE, GLenum renderAttach = 0, GLenum renderStorage = GL_DEPTH24_STENCIL8)
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(frameTarget, frameBuffer);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, formatTexture, w, h, 0, formatTexture, typeTextureData, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(frameTarget, frameAttach, GL_TEXTURE_2D, texture, 0);
	if (frameAttach == GL_DEPTH_ATTACHMENT)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	}
	if (renderAttach != 0)
	{
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, renderStorage, w, h);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, renderAttach, GL_RENDERBUFFER, rbo);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline void RenderTexture::Active(int activeTex = 0)
{
	glActiveTexture(GL_TEXTURE0 + activeTex);
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

inline GLuint RenderTexture::BufferObject()
{
	return frameBuffer;
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