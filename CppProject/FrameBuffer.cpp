#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const int w, const int h){
	sample = new Texture2D{ w, h };
	renderBuffer = new RenderBuffer{ w, h };
	width = w;
	height = h;

	targetFlag = GL_FRAMEBUFFER;

	glGenFramebuffers(1, &bufferID);
	glBindFramebuffer(targetFlag, bufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sample->textureID, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getID());

	glBindFramebuffer(targetFlag, 0);
}

FrameBuffer::~FrameBuffer(){
	glDeleteFramebuffers(1, &bufferID);

	delete sample;
	delete renderBuffer;
}

void FrameBuffer::resize(const int w, const int h){
	width = w;
	height = h;
	sample->resize(w, h);
	renderBuffer->resize(w, h);

	// bind(GL_FRAMEBUFFER);

	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sample->textureID, 0);
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getID());
	//
	// unbind();
}

bool FrameBuffer::check() const{
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void FrameBuffer::bind() const{
	glBindFramebuffer(targetFlag, bufferID);
}

void FrameBuffer::unbind() const{
	glBindFramebuffer(targetFlag, 0);
}

Texture2D& FrameBuffer::getTexture() const{
	return *sample;
}

GLuint FrameBuffer::getTextureID() const{
	return sample->textureID;
}
