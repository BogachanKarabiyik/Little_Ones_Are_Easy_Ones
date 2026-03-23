#pragma once
#include "Includes.h"

struct Writing
{
	GLuint writing[100];
	glm::vec2 position;
	uint8_t size;
	uint16_t length;
	glm::vec3 color;
};

struct TextPipeline
{
	uint8_t writingCount = 0;

	GLuint program;
	GLuint perspectiveLocation, modelLocation, writingLocation, colorLocation;
	GLuint texture;

	glm::mat4 model;

	Writing allWriting[100];

	void addWriting(std::string writing, uint8_t size, glm::vec3 color, glm::vec2 position)
	{
		allWriting[writingCount].size = size;
		allWriting[writingCount].position = position;
		allWriting[writingCount].color = color;

		for (int i = 0; i < writing.size(); i++)
		{
			unsigned char a = writing[i] - 32;
			if (!(i % 4))
				allWriting[writingCount].writing[(int)(i / 4) + 1] = a;
			else
				allWriting[writingCount].writing[(int)(i / 4) + 1] = allWriting[writingCount].writing[(int)(i / 4) + 1] | a;
			if ((i + 1) % 4)
				allWriting[writingCount].writing[(int)(i / 4) + 1] = allWriting[writingCount].writing[(int)(i / 4) + 1] << 8;
		}
		for (int i = writing.size() % 4; i < 3 && writing.size() % 4; i++)
		{
			allWriting[writingCount].writing[(int)((writing.size() - 1) / 4) + 1] = allWriting[writingCount].writing[(int)((writing.size() - 1) / 4) + 1] << 8;
		}
		allWriting[writingCount].length = writing.size();

		writingCount++;
	}

	void changeWriting(std::string writing, uint8_t size, glm::vec3 color, glm::vec2 position, uint8_t writingNo)
	{
		allWriting[writingNo].size = size;
		allWriting[writingNo].position = position;
		allWriting[writingNo].color = color;

		for (int i = 0; i < writing.size(); i++)
		{
			unsigned char a = writing[i] - 32;
			if (!(i % 4))
				allWriting[writingNo].writing[(int)(i / 4) + 1] = a;
			else
				allWriting[writingNo].writing[(int)(i / 4) + 1] = allWriting[writingNo].writing[(int)(i / 4) + 1] | a;
			if ((i + 1) % 4)
				allWriting[writingNo].writing[(int)(i / 4) + 1] = allWriting[writingNo].writing[(int)(i / 4) + 1] << 8;
		}
		for (int i = writing.size() % 4; i < 3 && writing.size() % 4; i++)
		{
			allWriting[writingNo].writing[(int)((writing.size() - 1) / 4) + 1] = allWriting[writingNo].writing[(int)((writing.size() - 1) / 4) + 1] << 8;
		}
		allWriting[writingNo].length = writing.size();
	}

	void render()
	{
		modelLocation = glGetUniformLocation(program, "model");
		writingLocation = glGetUniformLocation(program, "writing");
		perspectiveLocation = glGetUniformLocation(program, "perspective");
		colorLocation = glGetUniformLocation(program, "color");
		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

		glBindTexture(GL_TEXTURE_2D, texture);
		for (int i = 0; i < writingCount; i++)
		{
			model = glm::translate(glm::mat4(1.0f), glm::vec3(allWriting[i].position, 0));
			model *= glm::scale(glm::mat4(1.0f), glm::vec3(allWriting[i].size, allWriting[i].size, 0.f));

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(colorLocation, 1, glm::value_ptr(allWriting[i].color));
			glUniform1uiv(writingLocation, 100, allWriting[i].writing);
			
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, allWriting[i].length);
		}
	}

};