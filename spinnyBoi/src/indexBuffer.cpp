#include "indexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: count(count) {
	ASSERT(sizeof(GLuint) == sizeof(unsigned int));

	glCall(glGenBuffers(1, &rendererID));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	glCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}