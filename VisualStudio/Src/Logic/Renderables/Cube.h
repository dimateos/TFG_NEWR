#pragma once
#include <glm.hpp>

#include "../Renderable.h"
#include "../../Render/Shader.h"

class Cube : public Renderable
{
public:
	Cube();
	virtual ~Cube();

	virtual void draw(float delta, glm::mat4 modelMatrix);

protected:
	Shader triangleRGBShader;
	unsigned int trgb_VAO, trgb_VBO;
	float t_rgb_l = 0.2f;
	float triangle_vertices_rgb[6*3] = {
		// positions				// colors
		-t_rgb_l, -t_rgb_l, 0.0f,	1.0f, 0.0f, 0.0f,   // bottom right
		t_rgb_l, -t_rgb_l, 0.0f,	0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  t_rgb_l, 0.0f,		0.0f, 0.0f, 1.0f    // top
	};
};
