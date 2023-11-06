#pragma once
#include <glad/glad.h>

#include "VertexBuffer.h"
#include "AttributeLayout.h"

// All VAOs should be constructed at one load function.

namespace Graphic{
	class VertexArray
	{
		GLuint arrayID = 0;

	public:
		VertexArray(const VertexArray& other) = delete;

		VertexArray(VertexArray&& other) = delete;

		VertexArray& operator=(const VertexArray& other) = delete;

		VertexArray& operator=(VertexArray&& other) = delete;

		VertexArray() {
			glGenVertexArrays(1, &arrayID);
		}

		~VertexArray() {
			glDeleteVertexArrays(1, &arrayID);
		}

		void bind() const {
			glBindVertexArray(arrayID);
		}

		void unbind() const {
			glBindVertexArray(0);
		}

		void addBuffer(const VertexBuffer& vertices, const AttributeLayout& layout){
			vertices.bind();

			layout.generateAttributePointer();
		}
	};
}


