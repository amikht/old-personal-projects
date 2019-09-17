#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include "error.h"

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int rendererID;
};