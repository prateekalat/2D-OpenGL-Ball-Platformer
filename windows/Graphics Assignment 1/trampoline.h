#pragma once

#include "main.h"

class Trampoline
{
public:

	Trampoline() {}
	Trampoline(float x, float y, color_t color);
	glm::vec3 position;
	glm::vec3 velocity;
	float rotation;
	void draw(glm::mat4 VP);
	void tick();
	bounding_box_t bounding_box();
private:
	VAO * object;
	static constexpr GLfloat vertex_buffer_data[] = {
		-1.0f, -0.1f, +0.0f, // vertex 1
		-1.0f, +0.1f, +0.0f, // vertex 2
		+1.0f, -0.1f, +0.0f, // vertex 3

		+1.0f, +0.1f, +0.0f, // vertex 1
		-1.0f, +0.1f, +0.0f, // vertex 2
		+1.0f, -0.1f, +0.0f, // vertex 3
	};

	constexpr static float width = 2.0f;
	constexpr static float height = 0.2f;
};

