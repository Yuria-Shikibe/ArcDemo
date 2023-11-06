#pragma once
#include "FrameBuffer.h"

class MultiSampleFrameBuffer final : virtual public FrameBuffer
{
public:
	MultiSampleFrameBuffer(const int w, const int h, const int texSamples, const int renderSamples) : FrameBuffer(w, h){
		bind();

		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, sample->textureID);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, texSamples, GL_RGB, width, height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, sample->textureID, 0);

		renderBuffer->bind();
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, renderSamples, GL_DEPTH24_STENCIL8, width, height);
		renderBuffer->unbind();

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getID());

	}

	MultiSampleFrameBuffer(const int w, const int h) : MultiSampleFrameBuffer(w, h, 8, 8){
		
	}
};

