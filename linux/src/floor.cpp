#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "floor.h"
#include "main.h"

static GLfloat vertex_buffer_data[] = {
	-SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 1
	-SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 2
	+SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 3

	+SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 1
	-SCREEN_SIZE_X, +0.1f, +0.0f, // vertex 2
	+SCREEN_SIZE_X, -0.1f, +0.0f, // vertex 3
};

Floor::Floor(float x, float y, color_t color, float scale_x)
{
	this->scale_x = scale_x;
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;

	this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Floor::draw(glm::mat4 VP) {
	Matrices.model = glm::scale(glm::vec3(this->scale_x, 1.0f, 1.0f));
	glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	rotate = rotate * glm::translate(glm::vec3(0, -0.6f, 0));
	Matrices.model = translate * rotate * Matrices.model;
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Floor::tick() {
}

bounding_box_t Floor::bounding_box() {
	float x = this->position.x, y = this->position.y;
	bounding_box_t bbox = { x, y, 2.0f * SCREEN_SIZE_X * scale_x, 0.2f };
	return bbox;
}
