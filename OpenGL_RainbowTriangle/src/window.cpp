// HOLY CRAP ITS A RECTANGLE

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#ifdef RELEASE
#include <iostream>
#endif
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#define ASSERT(x) if (!(x)) __builtin_trap();
#define glCall(x) clearError();x;checkError(#x, __FILE__, __LINE__);

// Vertex buffer
unsigned int buffer;

static void clearError() {
	while (!glGetError);
}

static bool checkError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		#ifndef RELEASE
		std::cout << "[OpenGL Error] (" << error  << ") "
		          << function << std::endl
		          << file << ":" << line << std::endl;
		#endif
		return false;
	}
	return true;
}

struct ShaderSource {
	std::string vertex;
	std::string fragment;
};

static ShaderSource parseShader(const std::string& path) {
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

static unsigned int compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//TODO: Error handling 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		#ifndef RELEASE
		std::cerr << "Failed to compile shader: " << message << std::endl;
		#endif

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(int argc, char const *argv[]) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Window window(sf::VideoMode(900, 900), "Oof", sf::Style::None, settings);

	window.setFramerateLimit(60);

	float r = 1.0f;
	float g = 0.0f;
	float b = 0.0f;


	// Initialize GLEW. Must happen after window creation.
	if (glewInit() != GLEW_OK) {
		#ifndef RELEASE
		std::cerr << "Error initializing GLEW!" << std::endl;
		#endif
	}

	// Print OpenGL version:
	//std::cout << glGetString(GL_VERSION) << std::endl;

	float pi = atan(1) * 4;
	float dTheta = -0.1f;

	float positions[] = {
		-.693f, -.4f, // 0
		.693f, -.4f, // 1
		0.0f, 0.8f   // 2
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	glCall(glGenBuffers(1, &buffer));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	glCall(glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

	// Enable vertex attribute index 0
	glCall(glEnableVertexAttribArray(0));
	// Define attribute 0 of our vertex buffer
	glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glCall(ShaderSource source = parseShader("res\\shaders\\basic.shd"));

	//// Proof that the parsing function worked correctly
	// std::cout << "VERTEX"        << std::endl;
	// std::cout << source.vertex   << std::endl;
	// std::cout << "FRAGMENT"      << std::endl;
	// std::cout << source.fragment << std::endl;

	unsigned int shader = createShader(source.vertex, source.fragment);
	glCall(glUseProgram(shader));

	glCall(int posUniform = glGetUniformLocation(shader, "u_dTheta"));
	ASSERT(posUniform != -1);

	glCall(int colorUniform = glGetUniformLocation(shader, "u_Color"));
	ASSERT(colorUniform != -1);

	glCall(glUniform1f(posUniform, dTheta));
	glCall(glUniform4f(colorUniform, r, g, b, 1.0));

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch(e.type) {
				case sf::Event::Closed:
					window.close();
					return 0;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		//// Update things here
		// Edit this later to actually work:
		if (r > 0.0f && b == 0) {
			r -= 0.01;
			g += 0.01;
		}
		else if (g > 0.0f) {
			g -= 0.01;
			b += 0.01;
		}
		else {
			b -= 0.01;
			r += 0.01;
		}
		if (r < 0)
			r = 0;
		if (g < 0)
			g = 0;
		if (b < 0)
			b = 0;

		if (dTheta >= 2 * pi)
			dTheta = 0;
		dTheta += 0.01f;
		//// Draw things here
		// Draws the triangle
		glCall(glUniform1f(posUniform, dTheta));
		glCall(glUniform4f(colorUniform, r, g, b, 1.0f));
		glCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

		//// End drawing and flip the display
		window.display();

	}

	return 0;
}
