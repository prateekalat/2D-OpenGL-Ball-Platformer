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
};
