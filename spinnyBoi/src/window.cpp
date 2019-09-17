// HOLY CRAP ITS A RECTANGLE

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <cmath>

#include "error.h"
#include "vertexArray.h"
#include "bufferLayout.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "shader.h"

int main(int argc, char const *argv[]) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	int WIDTH = 16 * 80;
	int HEIGHT = 9 * 80;
	float aspectRatio = (float)WIDTH / (float)HEIGHT;

	sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "Its working!", sf::Style::None, settings);

	window.setFramerateLimit(60);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Error initializing GLEW!" << std::endl;
	}

	// float positions[] = {
	// 	-0.5f,  0.5f, -0.5f, 1.0f, //0
	// 	-0.5f, -0.5f, -0.5f, 1.0f, //1
	// 	 0.5f,  0.5f, -0.5f, 1.0f, //2
	// 	 0.5f, -0.5f, -0.5f, 1.0f, //3
	// 	-0.5f,  0.5f,  0.5f, 1.0f, //4
	// 	-0.5f, -0.5f,  0.5f, 1.0f, //5
	// 	 0.5f,  0.5f,  0.5f, 1.0f, //6
	// 	 0.5f, -0.5f,  0.5f, 1.0f  //7
	// };
	std::vector<float> positions = {
		-0.5f,  0.5f, -0.5f, 1.0f, //0
	 	-0.5f, -0.5f, -0.5f, 1.0f, //1
	 	 0.5f,  0.5f, -0.5f, 1.0f, //2
	 	 0.5f, -0.5f, -0.5f, 1.0f, //3
	 	-0.5f,  0.5f,  0.5f, 1.0f, //4
	 	-0.5f, -0.5f,  0.5f, 1.0f, //5
	 	 0.5f,  0.5f,  0.5f, 1.0f, //6
	 	 0.5f, -0.5f,  0.5f, 1.0f  //7
	};


	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 6,
		6, 3, 7,
		6, 7, 5,
		6, 5, 4,
		0, 1, 4,
		4, 1, 5,
		0, 4, 6,
		0, 6, 2,
		1, 5, 7,
		1, 7, 3
	};

	float projection[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float translation[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float rotation[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float fov = 3.1415926535f / 2.0f;
	float zNear = 0.01f;
	float zFar = 1000.0f;


	VertexArray* va = new VertexArray();
	va->bind();

	VertexBuffer* vb = new VertexBuffer(positions.data(), 8*4*sizeof(float));

	BufferLayout layout;
	layout.push(GL_FLOAT, 4);

	va->addBuffer(vb, layout);

	IndexBuffer* ib = new IndexBuffer(indices.data(), 12 * 3);

	Shader* shader = new Shader("res\\shaders\\basic.shd");

	glCall(int u_ColorLocation = glGetUniformLocation(shader->program, "u_Color"));
	glCall(int u_Projection = glGetUniformLocation(shader->program, "u_Projection"));
	glCall(int u_Translation = glGetUniformLocation(shader->program, "u_Translation"));
	glCall(int u_Rotation = glGetUniformLocation(shader->program, "u_Rotation"));

	float r = 1.0f;
	float delta = 0.01f;
	float theta = 0.0f;

	bool running = true;

	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;

	while (running) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch(e.type) {
				case sf::Event::Closed:
					running = false;
					break;
				case sf::Event::KeyPressed:
					switch(e.key.code) {
						case sf::Keyboard::W:
							backward = true;
							break;
						case sf::Keyboard::S:
							forward = true;
							break;
						case sf::Keyboard::A:
							left = true;
							break;
						case sf::Keyboard::D:
							right = true;
					}
					break;
				case sf::Event::KeyReleased:
					switch(e.key.code) {
						case sf::Keyboard::W:
							backward = false;
							break;
						case sf::Keyboard::S:
							forward = false;
							break;
						case sf::Keyboard::A:
							left = false;
							break;
						case sf::Keyboard::D:
							right = false;
					}
			}
		}

		if (r < 0.0f)
			delta = 0.01f;
		else if (r > 1.0f)
			delta = -0.01f;
		r += delta;

		if (forward)
			translation[2*4 + 3] += 0.01f;
		if (backward)
			translation[2*4 + 3] -= 0.01f;

		if (left)
			theta += 0.01f;
		if (right)
			theta -= 0.01f;


		projection[0*4 + 0] = 1.0f / (aspectRatio * tan(fov / 2.0f));
		projection[1*4 + 1] = 1.0f / tan(fov / 2.0f);
		projection[2*4 + 2] = (-zNear - zFar) / (zNear - zFar);
		projection[2*4 + 3] = (2 * zFar * zNear) / (zNear - zFar);
		projection[3*4 + 2] = 1;

		rotation[0*4 + 0] = cos(theta);
		rotation[0*4 + 2] = -sin(theta);
		rotation[2*4 + 0] = sin(theta);
		rotation[2*4 + 2] = cos(theta);

		glCall(glClear(GL_COLOR_BUFFER_BIT));

		shader->bind();
		glCall(glUniform4f(u_ColorLocation, r, 0.4f, 1.0f, 1.0f));
		glCall(glUniformMatrix4fv(u_Projection, 1, GL_TRUE, projection));
		glCall(glUniformMatrix4fv(u_Translation, 1, GL_TRUE, translation));
		glCall(glUniformMatrix4fv(u_Rotation, 1, GL_TRUE, rotation))

		va->bind();
		ib->bind();

		// Draw things here
		glCall(glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr));

		// End drawing and flip the display
		window.display();

	}

	delete va;
	delete vb;
	delete ib;
	delete shader;

	window.close();

	return 0;
}
