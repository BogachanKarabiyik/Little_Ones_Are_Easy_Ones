#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

struct Writing
{
	GLuint writing[100];

	glm::vec2 location;

	glm::mat4 model;
	glm::vec4 size_color;

	GLuint model_loc, writing_loc, size_color_loc;

	std::string text;
	uint16_t text_length, text_size;

	void write()
	{
		text_length = text.length();
		for (int i = 0; i < text_length; i++)
		{
			if (!(i % 4))
				writing[(int)(i / 4) + 1] = (text[i] - 32);
			else
				writing[(int)(i / 4) + 1] = writing[(int)(i / 4) + 1] | (text[i] - 32);
			if ((i + 1) % 4)
				writing[(int)(i / 4) + 1] = writing[(int)(i / 4) + 1] << 8;
		}
		for (int i = text_length % 4; i < 3 && text_length % 4; i++)
		{
			writing[(int)((text_length - 1) / 4) + 1] = writing[(int)((text_length - 1) / 4) + 1] << 8;
		}
		writing[0] = text_length;

		model = glm::translate(glm::mat4(1.0f), glm::vec3(location.x, location.y, 0.0));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3((float)text_size, (float)text_size, 0.f));
	}

	Writing(const char* inner_text, uint16_t inner_text_length, uint16_t inner_text_size, glm::vec2 inner_location) :
		text(inner_text), text_size(inner_text_size), location(inner_location)
	{
		text_length = text.length();

		for (int i = 0; i < 100; i++)
		{
			writing[i] = 0;
		}

		size_color = glm::vec4(inner_text_size, 1.0, 1.0, 1.0);

		write();
	}

	void update()
	{
		write();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(location.x, location.y, 0.0));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3((float)size_color.x, (float)size_color.x, 0.f));
	}
};