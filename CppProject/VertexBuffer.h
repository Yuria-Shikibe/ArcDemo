#pragma once

#include <glad/glad.h>

#include "AbstractBuffer.h"

namespace Graphic{
	class VertexBuffer : virtual public AbstractBuffer
	{

	public:
		VertexBuffer() {
			glGenBuffers(1, &bufferID);
			targetFlag = GL_ARRAY_BUFFER;
		}

		~VertexBuffer() override {
			glDeleteBuffers(1, &bufferID);
		}

		VertexBuffer(const VertexBuffer& other) = delete;

		VertexBuffer(VertexBuffer&& other) = delete;

		VertexBuffer& operator=(const VertexBuffer& other) = delete;

		VertexBuffer& operator=(VertexBuffer&& other) = delete;

		void bind() const override {
			glBindBuffer(targetFlag, bufferID);
		}

		inline GLuint getID() const {
			return bufferID;
		}

		template <typename T>
		void setData(const T* data, const GLsizei count, const GLenum mode = GL_DYNAMIC_DRAW) {
			glBufferData(targetFlag, count * sizeof(T), data, mode);
		}

		template <typename T, size_t size>
		void setData(const T(&arr)[size], const GLenum mode = GL_DYNAMIC_DRAW) {
			glBufferData(targetFlag, size * sizeof(T), &arr, mode);
		}

		void setDataRaw(const void* data, const GLuint size, const GLenum mode = GL_DYNAMIC_DRAW) const{
			glBufferData(targetFlag, size, data, mode);
		}

		void unbind() const override {
			glBindBuffer(targetFlag, 0);
		}
	};
}
