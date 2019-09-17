#include "error.h"

void clearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool checkError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "):" << function << std::endl
		          << file << ":" << line << std::endl;
		return false;
	}
	return true;
}