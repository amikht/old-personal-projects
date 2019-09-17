#include "shader.h"

Shader::Shader(std::string path) {
	glCall(program = glCreateProgram());
	sources = parse(path);

	unsigned int vs = compile(GL_VERTEX_SHADER, sources.vertex);
	unsigned int fs = compile(GL_FRAGMENT_SHADER, sources.fragment);

	glCall(glAttachShader(program, vs));
	glCall(glAttachShader(program, fs));

	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	glCall(glUseProgram(program));
}

Shader::~Shader() {}

void Shader::bind() {
	glCall(glUseProgram(program));
}

shaderSource Shader::parse(const std::string& path) {
	std::ifstream file(path);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	std::string line;
	while(getline(file, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;

			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile(unsigned int type, const std::string& source) {
	glCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();

	glCall(glShaderSource(id, 1, &src, nullptr));
	glCall(glCompileShader(id));

	int result;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));

		glCall(glGetShaderInfoLog(id, length, &length, message));
		std::cerr << "Failed to compile shader: " << message << std::endl;

		glCall(glDeleteShader(id));
		return 0;
	}

	return id;
}