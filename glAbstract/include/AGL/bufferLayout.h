#pragma once

#include <vector>
#include "error.h"

struct BufferElement {
	unsigned int type;
	unsigned int count;
	bool isNormalized;

	static unsigned int getSize(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout {
public:
	BufferLayout();
	~BufferLayout();

	const std::vector<BufferElement>& getElements();
	unsigned int getStride();
	
	void push(unsigned int type, unsigned int count);
	
private:
	std::vector<BufferElement> elements;
	unsigned int stride;
};