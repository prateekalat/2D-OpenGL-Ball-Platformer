#pragma once

#include "main.h"

class Floor
{
public:
	Floor() {}
	Floor(float x, float y, color_t color) : Floor(x, y, color, 1.0f) {}
	Floor(float x, float y, color_t color, float scale_x);
	glm::vec3 position;
	float rotation;
	float scale_x = 1.0f;
	void draw(glm::mat4 VP);
	void tick();
	bounding_box_t bounding_box();
private:
	VAO * object;
	static constexpr GLfloat vertex_buffer_data[] = {
		-SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 1
		-SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 2
		+SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 3

		+SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 1
		-SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 2
		+SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 3
	};
};


