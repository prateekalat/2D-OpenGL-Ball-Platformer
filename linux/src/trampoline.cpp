#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "trampoline.h"
#include "main.h"

static GLfloat vertex_buffer_data[] = {
	-1.0f, -0.1f, +0.0f, // vertex 1
	-1.0f, +0.1f, +0.0f, // vertex 2
	+1.0f, -0.1f, +0.0f, // vertex 3

	+1.0f, +0.1f, +0.0f, // vertex 1
	-1.0f, +0.1f, +0.0f, // vertex 2
	+1.0f, -0.1f, +0.0f, // vertex 3
};

static float width = 2.0f;
static float height = 0.2f;

Trampoline::Trampoline(float x, float y, color_t color) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	this->velocity = glm::vec3(-0.01f, 0.0f, 0.0f);
	this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Trampoline::tick() {
	this->position += this->velocity;

	if (abs(this->position.x) > SCREEN_SIZE_X)
		this->velocity = -this->velocity;
}

bounding_box_t Trampoline::bounding_box() {
	float x = this->position.x, y = this->position.y;
	bounding_box_t bbox = { x, y, width, height };
	return bbox;
}
