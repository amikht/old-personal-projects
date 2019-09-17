#include "vertexArray.h"

VertexArray::VertexArray() {
	glCall(glGenVertexArrays(1, &id));\
	bind();
}
VertexArray::~VertexArray() {

}

void VertexArray::bind() const {
	glCall(glBindVertexArray(id));
}

void VertexArray::addBuffer(VertexBuffer* vb, BufferLayout layout) {
	bind();
	vb->bind();
	const auto& elements = layout.getElements();
	
	for (int i = 0; i < elements.size(); ++i) {
		BufferElement element = elements[i];

		unsigned long long offset = 0;

		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element.count, element.type,
			element.isNormalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)offset));
		
		offset += BufferElement::getSize(element.type) * element.count;
	}
}
