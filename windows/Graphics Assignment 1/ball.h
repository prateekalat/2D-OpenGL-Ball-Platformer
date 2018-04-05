#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
	glm::vec3 gravity;
    float rotation;
	float RADIUS = 0.3f;

	glm::vec3 collision = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 color = glm::vec3(0.3f, 1.0f, 0.6f);
	void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
	void boost();
	void boost(float angle);
	void superBoost();
	void checkBounds();
	void respawn();
	void changeColor(glm::vec3 color);

	bool invincible = false;

	unsigned int invincibilityTimer = 0;

    glm::vec3 velocity;
	glm::vec3 acceleration;
    bounding_box_t bounding_box();
private:
    VAO *object;
	float delta = 0.1f;
};

#endif // BALL_H
