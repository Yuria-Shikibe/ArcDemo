#pragma once
#include "AbstractBuffer.h"

namespace Graphic{
	class RenderBuffer : virtual public AbstractBuffer{
	protected:
		int width, height;
	public:
		RenderBuffer(const int w, const int h) : width(w), height(h){
			glGenRenderbuffers(1, &bufferID);
			targetFlag = GL_RENDERBUFFER;
			bind();

			glRenderbufferStorage(targetFlag, GL_DEPTH24_STENCIL8, w, h);
			unbind();
		}

		~RenderBuffer() override{
			glDeleteRenderbuffers(1, &bufferID);
		}

		void bind() const override{
			glBindRenderbuffer(targetFlag, bufferID);
		}

		void unbind() const override{
			glBindRenderbuffer(targetFlag, 0);
		}

		void resize(const int w, const int h){
			width = w;
			height = h;
			bind();
			glRenderbufferStorage(targetFlag, GL_DEPTH24_STENCIL8, w, h);
			unbind();
		}
	};
}


