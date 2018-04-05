#pragma once

#include "main.h"

class Water
{
public:
	Water() {}
	Water(float x, float y, color_t color);
	glm::vec3 position;
	float rotation;
	float RADIUS = 3.0f;

	void draw(glm::mat4 VP);
	void tick();
	bounding_box_t bounding_box();
private:
	VAO * object;
};

