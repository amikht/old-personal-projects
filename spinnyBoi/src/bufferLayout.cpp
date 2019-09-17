#include "bufferLayout.h"

BufferLayout::BufferLayout()
	: stride(0) {}

BufferLayout::~BufferLayout() {}

const std::vector<BufferElement>& BufferLayout::getElements() {
	return elements;
}
unsigned int BufferLayout::getStride() {
	return stride;
}

void BufferLayout::push(unsigned int type, unsigned int count) {
	switch(type) {
		case GL_FLOAT:
			elements.push_back({GL_FLOAT, count, false});
			stride += sizeof(GLfloat) * count;
			break;
		case GL_UNSIGNED_INT:
			elements.push_back({GL_UNSIGNED_INT, count, false});
			stride += sizeof(GLuint) * count;
			break;
		default:
			ASSERT(false);
	}
}