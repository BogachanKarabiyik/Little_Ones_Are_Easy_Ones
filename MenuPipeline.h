#pragma once

#include "Includes.h"

struct MenuItem
{
	glm::vec3 color;
	glm::vec2 position;
	glm::vec2 scale;
};

struct MenuPipeline
{
	GLuint program;
	GLuint breadProgram;
	GLuint perspectiveLocation, modelLocation, colorLocation;

	glm::mat4 model;

	GLuint texture;
	GLuint bread;

	uint8_t menuCount = 0;

	MenuItem menu[100];

	glm::vec3 breadPos = glm::vec3(0, 0, 0);

	void addMenu(glm::vec3 color, glm::vec2 pos, glm::vec2 scale)
	{
		menu[menuCount].color = color;
		menu[menuCount].position = pos;
		menu[menuCount].scale = scale;

		menuCount++;
	}

	void render()
	{
		for (int i = 0; i < menuCount; i++)
		{
			modelLocation = glGetUniformLocation(program, "model");
			perspectiveLocation = glGetUniformLocation(program, "perspective");
			colorLocation = glGetUniformLocation(program, "color");
			glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

			glBindTexture(GL_TEXTURE_2D, texture);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(menu[i].position, 0));
			model *= glm::scale(glm::mat4(1.0f), glm::vec3(menu[i].scale, 0));

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(colorLocation, 1, glm::value_ptr(menu[i].color));

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	void renderBread()
	{
		modelLocation = glGetUniformLocation(program, "model");
		perspectiveLocation = glGetUniformLocation(program, "perspective");
		colorLocation = glGetUniformLocation(program, "color");
		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

		glBindTexture(GL_TEXTURE_2D, bread);

		model = glm::translate(glm::mat4(1.0f), breadPos);
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(50, 50, 0));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};