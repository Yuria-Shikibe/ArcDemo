#include "IndexBuffer.h"

Graphic::IndexBuffer::IndexBuffer(){
	glGenBuffers(1, &bufferID);
	targetFlag = GL_ELEMENT_ARRAY_BUFFER;
}

Graphic::IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1, &bufferID);
}

void Graphic::IndexBuffer::bind() const{
	glBindBuffer(targetFlag, bufferID);
}

void Graphic::IndexBuffer::setDataRaw(const GLuint* data, const GLsizei count, const GLenum mode){
	glBufferData(targetFlag, static_cast<long long>(sizeof(GLuint)) * count, data, mode);
	bufferSize = count;
}

void Graphic::IndexBuffer::unbind() const{
	glBindBuffer(targetFlag, 0);
}

GLsizei Graphic::IndexBuffer::getSize() const{
	return bufferSize;
}
