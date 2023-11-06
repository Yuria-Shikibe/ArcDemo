#include "AttributeLayout.h"

#include "Graphic.h"

void Graphic::AttributeLayout::add(const GLenum type, const GLint size, const GLboolean normalized){
	elems.push_back({ type, normalized, size });
	stride += sizeofType(type) * size;
}

void Graphic::AttributeLayout::addFloat(const GLint size){
	add(GL_FLOAT, size);
}

void Graphic::AttributeLayout::generateAttributePointer() const{
	unsigned int offset = 0;

	for(unsigned int i = 0; i < elems.size(); i++){
		const auto& [type, normalized, size] = elems.at(i);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, size, type, normalized, stride, reinterpret_cast<const void*>(offset));  // NOLINT(performance-no-int-to-ptr)
		offset += size * sizeofType(type);
	}
}
