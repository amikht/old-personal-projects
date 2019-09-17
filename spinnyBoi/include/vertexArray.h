#pragma once

#include "vertexBuffer.h"
#include "bufferLayout.h"
#include "error.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();

	void addBuffer(VertexBuffer* vb, BufferLayout layout);

private:
	unsigned int id;
};