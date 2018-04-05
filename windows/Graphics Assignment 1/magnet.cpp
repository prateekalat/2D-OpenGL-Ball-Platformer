#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "main.h"
#include "magnet.h"


Magnet::Magnet(float x, float y, color_t color) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	this->velocity = glm::vec3(-0.01f, 0.0f, 0.0f);
	this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Magnet::tick() {
	directionCount++;

	if (directionCount == 180)
	{
		float multiplier = (left) ? 1.0f : -1.0f;
		this->position = glm::vec3(multiplier * (SCREEN_SIZE_X - 3.0f), 0.0f, 0.0f);
		left = !left;
		directionCount = 0;
		rotation += 180.0f;
	}
}

bounding_box_t Magnet::bounding_box() {
	float x = this->position.x, y = this->position.y;
	bounding_box_t bbox = { x, y, width, height };
	return bbox;
}

