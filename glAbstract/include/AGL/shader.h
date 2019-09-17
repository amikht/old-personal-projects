#pragma once

#include <string>
#include <sstream>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include "error.h"

struct shaderSource {
	std::string vertex;
	std::string fragment;
};

class Shader {
public:
	Shader(std::string path);
	~Shader();

	void bind();

	unsigned int program;

private:
	shaderSource parse(const std::string& path);
	unsigned int compile(unsigned int type, const std::string& source);

	shaderSource sources;
};