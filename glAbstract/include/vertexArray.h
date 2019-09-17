#pragma once

#include "vertexBuffer.h"
#include "bufferLayout.h"
#include "error.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;

	void addBuffer(VertexBuffer* vb, BufferLayout layout);

private:
	unsigned int id;
};