#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
	this->gravity = gravityConst;
    this->rotation = 0;
	velocity = glm::vec3(0.0, 0.0, 0.0);
	acceleration = glm::vec3(0.0, 0.0, 0.0);

	GLfloat vertex_buffer_data[1000] = { 0.0f };
	int n = 100;
	float angle = (2 * M_PI) / n;

	for (int i = 0; i<n; i++)
	{
		for (int j = 1; j<3; j++)
		{
			vertex_buffer_data[9 * i + 3 * j] = RADIUS * cos((i + j - 1)*angle);
			vertex_buffer_data[9 * i + 3 * j + 1] = RADIUS * sin((i + j - 1)*angle);
			vertex_buffer_data[9 * i + 3 * j + 2] = 0.0f;
		}
	}

    this->object = create3DObject(GL_TRIANGLES, 300, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::boost()
{
	if (!invincible)
	{
		this->velocity.y = +0.35f;
	}
	else
	{
		this->velocity.y = 0.70f;
	}
}

void Ball::boost(float angle)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 temp = rotationMatrix * glm::vec4(0.0f, 0.35f, 0.0f, 1.0f);

	this->velocity = glm::vec3(temp.x, temp.y, temp.z);

	std::cout << angle << " (" << this->velocity.x << ", " << this->velocity.y << ")" << std::endl;
}

void Ball::superBoost()
{
	this->velocity.y = +0.9f;
}

void Ball::tick() {
    acceleration += gravity * this->collision.y;
	acceleration -= glm::vec3(0.05f, 0.001f, 0.05f) * velocity;
	this->velocity += acceleration;
	this->position += velocity;

	if (abs(this->position.x) > SCREEN_SIZE_X)
		this->velocity.x = -this->velocity.x;

	if (this->position.y > SCREEN_SIZE_Y)
	{
		this->velocity.y = -0.1f * this->velocity.y;
		this->position.y -= 0.1f;
	}
		
	if (invincible)
	{
		//std::cout << invincibilityTimer << std::endl;

		invincibilityTimer++;

		if (invincibilityTimer >= 300)
		{
			invincible = false;
			changeColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else {
			if (color.b > 1.0f)
				delta = -0.1f;
			else if (color.b < 0.0f)
				delta = 0.1f;

			color.b += delta;

			changeColor(color);
		}
	}
}

void Ball::changeColor(glm::vec3 color)
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

void Ball::checkBounds()
{
	if (abs(this->position.x) > SCREEN_SIZE_X + 1.0f || abs(this->position.y) > SCREEN_SIZE_Y + 1.0f)
	{
		respawn();
	}
}

void Ball::respawn()
{
	this->position.x = 0.0f;
	this->position.y = 2.0f;
	this->velocity = this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 2.0f * RADIUS, 2.0f * RADIUS };
    return bbox;
}
