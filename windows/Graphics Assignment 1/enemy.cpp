#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "main.h"
#include "enemy.h"

Enemy::Enemy(color_t color) {
	this->spawn();
	this->position = glm::vec3(this->position.x, this->position.y, 0);

	this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	//rotate = rotate * glm::translate(glm::vec3(0, , 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Enemy::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
	this->position += velocity;

	if (abs(this->position.x) > SCREEN_SIZE_X)
		this->spawn();

	if (this->invincible)
	{
		if (this->color.b > 1.0f)
			delta = -0.1f;
		else if (color.b < 0.0f)
			delta = 0.1f;

		color.b += delta;

		changeColor(color);
	}
}

void Enemy::spawn()
{
	bool wasInvincible = this->invincible;

	float direction = (rand() % 2) ? 1.0f : -1.0f;
	this->position.x = -SCREEN_SIZE_X * direction;
	this->position.y = -2.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4.0f - (-2.5f))));
	this->velocity.x = direction * static_cast <float> (0.02f + (rand()) / (static_cast <float> (RAND_MAX / ((0.04f - 0.02f)))));
	this->invincible = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.0f))) > 0.95f;

	this->rotation = -30.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (30.0f - (-30.0f))));

	if (this->invincible && !wasInvincible)
		this->color = glm::vec3(0.3f, 1.0f, 0.6f);
	else
		this->color = glm::vec3(COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b) / 256.0f;

	if (!this->invincible && wasInvincible)
		this->changeColor(this->color);
}

bounding_box_t Enemy::bounding_box() {
	float x = this->position.x, y = this->position.y;
	bounding_box_t bbox = { x, y, 0.6, 0.6 };
	return bbox;
}

void Enemy::changeColor(glm::vec3 color)
{
	GLfloat *colors = new GLfloat[3 * this->object->NumVertices];

	for (int i = 0; i < 3 * this->object->NumVertices; i += 3)
	{
		colors[i] = color.r;
		colors[i + 1] = color.g;
		colors[i + 2] = color.b;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->object->ColorBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * this->object->NumVertices * sizeof(GLfloat), colors);

	delete colors;
}

