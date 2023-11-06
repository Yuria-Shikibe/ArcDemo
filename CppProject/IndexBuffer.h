#pragma once

#include <array>
#include <glad/glad.h>

#include "AbstractBuffer.h"

namespace Graphic{
	class IndexBuffer : virtual public AbstractBuffer
	{
	public:
		inline static constexpr int ELEMENTS_STD_LENGTH = 6;
		inline static const std::array<GLuint, ELEMENTS_STD_LENGTH> ELEMENTS_STD = {0, 2, 1, 2, 3, 0};

	protected:
		GLsizei bufferSize = 0;

	public:
		IndexBuffer();

		~IndexBuffer() override;

		IndexBuffer(const IndexBuffer& other) = delete;

		IndexBuffer(IndexBuffer&& other) = delete;

		IndexBuffer& operator=(const IndexBuffer& other) = delete;

		IndexBuffer& operator=(IndexBuffer&& other) = delete;

		void bind() const override;

		template <GLuint size>
		void setData(GLuint(&arr)[size], const GLenum mode = GL_DYNAMIC_DRAW) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, &arr, mode);
			bufferSize = size;
		}

		void setDataRaw(const GLuint* data, const GLsizei count, const GLenum mode = GL_DYNAMIC_DRAW);

		void unbind() const override;

		[[nodiscard]] GLsizei getSize() const;
	};
}
