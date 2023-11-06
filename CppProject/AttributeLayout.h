#pragma once
#include <vector>
#include <glad/glad.h>

namespace Graphic{
	struct VertElem{
		GLenum type;
		GLboolean normalized;
		GLint size;
	};

	class AttributeLayout
	{
	protected:
		GLsizei stride = 0;
		std::vector<VertElem> elems{};

	public:
		void add(const GLenum type, const GLint size, const GLboolean normalized = GL_FALSE);

		void addFloat(const GLint size);

		void generateAttributePointer() const;
	};
}


