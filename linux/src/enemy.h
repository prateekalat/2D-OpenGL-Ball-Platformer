#pragma once
#include "main.h"

class Enemy
{
public:
	Enemy() {}
	Enemy(color_t color);
	glm::vec3 position;
	float rotation;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void tick();
	void spawn();
	void changeColor(glm::vec3 color);
	glm::vec3 velocity;
	glm::vec3 color;
	glm::vec3 acceleration;
	bounding_box_t bounding_box();

	bool invincible = false;
	float delta = 0.1f;
private:
	VAO * object;
	
};
