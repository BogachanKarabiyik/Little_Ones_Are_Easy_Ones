#pragma once

#include "Includes.h"

struct Level
{
	GLuint block[289];
};

struct StaticPipeline
{
	GLuint program;
	GLuint perspectiveLocation, modelLocation, levelLocation;

	glm::mat4 model;

	GLuint texture;

	uint8_t staticCount = 0;

	Level level[100];

	void render(uint8_t levelNo)
	{
		modelLocation = glGetUniformLocation(program, "model");
		perspectiveLocation = glGetUniformLocation(program, "perspective");
		levelLocation = glGetUniformLocation(program, "level");
		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

		glBindTexture(GL_TEXTURE_2D, texture);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-640, -362.5, 0.f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(80.f, 80.f, 0.f));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1uiv(levelLocation, 288, level[levelNo].block);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 288);
	}

	void readTxt(uint8_t levelNo)
	{
		std::string line;
		std::ifstream MyReadFile("Saves/one.txt");

		uint8_t lineCounter = 0;
		while (std::getline(MyReadFile, line))
		{
			for (int i = 0; i < 16; i++)
			{
				level[levelNo].block[i + (16 * lineCounter)] = line[i];
			}
			lineCounter++;
		}

		MyReadFile.close();
	}
};