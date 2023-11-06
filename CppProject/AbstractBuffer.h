#pragma once
#include <glad/glad.h>

namespace Graphic{
	class AbstractBuffer
	{
	protected: GLuint bufferID = 0;
	protected: GLenum targetFlag = 0;

	public:
		AbstractBuffer(const AbstractBuffer& other) = delete;

		AbstractBuffer(AbstractBuffer&& other) = delete;

		AbstractBuffer& operator=(const AbstractBuffer& other) = delete;

		AbstractBuffer& operator=(AbstractBuffer&& other) = delete;

		virtual ~AbstractBuffer() = default;
		AbstractBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		GLuint getID() const{
			return bufferID;
		}
	};
}


