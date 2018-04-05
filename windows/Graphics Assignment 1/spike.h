#pragma once
class Spike
{
public:
#pragma once

#include "main.h"
public:
	Spike() {}
	Spike(float x, float y, color_t color);
	glm::vec3 position;
	glm::vec3 velocity;
	float rotation;
	void draw(glm::mat4 VP);
	void tick();
	bounding_box_t bounding_box();
private:
	VAO * object;
	static constexpr GLfloat vertex_buffer_data[] = {
		-0.6f, -0.3f, +0.0f, // vertex 1
		-0.2f, -0.3f, +0.0f, // vertex 2
		-0.4f, +0.3f, +0.0f, // vertex 3
				  
		-0.2f, -0.3f, +0.0f, // vertex 1
		+0.2f, -0.3f, +0.0f, // vertex 2
		+0.0f, +0.3f, +0.0f, // vertex 3
				  
		+0.2f, -0.3f, +0.0f, // vertex 1
		+0.6f, -0.3f, +0.0f, // vertex 2
		+0.4f, +0.3f, +0.0f, // vertex 3
	};

	constexpr static float width = 1.2f;
	constexpr static float height = 0.6f;
};

