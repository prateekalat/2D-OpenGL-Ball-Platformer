
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color)
{
	
	GLfloat vertex_buffer_data[1000] = { 0.0f };
	int n = 100;
	float angle = (2 * M_PI) / n;

	for (int i = n / 2; i < n; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			vertex_buffer_data[9 * i + 3 * j] = RADIUS * cos((i + j - 1)*angle);
			vertex_buffer_data[9 * i + 3 * j + 1] = RADIUS * sin((i + j - 1)*angle);
			vertex_buffer_data[9 * i + 3 * j + 2] = 0.0f;
		}
	}

	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;

	this->object = create3DObject(GL_TRIANGLES, 3 * n, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate(this->position);    // glTranslatef
	glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Water::tick() {
}

bounding_box_t Water::bounding_box() {
	float x = this->position.x, y = this->position.y;
	bounding_box_t bbox = { x, y - RADIUS, 2.0f * RADIUS, RADIUS };
	return bbox;
}

