#pragma once

#include "main.h"

class Magnet
{
public:
	Magnet() {}
	Magnet(float x, float y, color_t color);
	glm::vec3 position;
	glm::vec3 velocity;
	float rotation;
	void draw(glm::mat4 VP);
	void tick();

	bool left = true;
	int directionCount = 0;

	bounding_box_t bounding_box();
private:
	VAO * object;
	static constexpr GLfloat vertex_buffer_data[] = {
		+0.5f, +1.0f, +0.0f, // vertex 1
		+0.5f, +0.5f, +0.0f, // vertex 2
		-0.5f, +1.0f, +0.0f, // vertex 3

		-0.5f, +0.5f, +0.0f, // vertex 1
		+0.5f, +0.5f, +0.0f, // vertex 2
		-0.5f, +1.0f, +0.0f, // vertex 3

		-0.5f, +0.5f, +0.0f, // vertex 1
		-0.5f, -0.5f, +0.0f, // vertex 2
		+0.0f, -0.5f, +0.0f, // vertex 3

		-0.5f, +0.5f, +0.0f, // vertex 1
		+0.0f, +0.5f, +0.0f, // vertex 2
		+0.0f, -0.5f, +0.0f, // vertex 3

		+0.5f, -0.5f, +0.0f, // vertex 1
		-0.5f, -1.0f, +0.0f, // vertex 2
		+0.5f, -1.0f, +0.0f, // vertex 3

		-0.5f, -0.5f, +0.0f, // vertex 1
		-0.5f, -1.0f, +0.0f, // vertex 2
		+0.5f, -0.5f, +0.0f, // vertex 3
	};

	constexpr static float width = 30.0f;
	constexpr static float height = 2.0f;
};

