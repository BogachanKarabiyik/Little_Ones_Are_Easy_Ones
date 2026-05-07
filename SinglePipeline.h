#pragma once

#include "Includes.h"

struct SingleItem
{
	glm::vec2 position;
	glm::vec2 scale;
	uint8_t textureOffset;
};

struct SinglePipeline
{
	GLuint program;
	GLuint perspectiveLocation, modelLocation;

	glm::mat4 model;

	GLuint texture[100];

	uint8_t singleCount = 0;

	SingleItem singles[100];

	glm::vec2 direction = glm::vec2(1,0.5);

	void addSingle(glm::vec2 pos, glm::vec2 scale, uint8_t textureOffset)
	{
		singles[singleCount].position = pos;
		singles[singleCount].scale = scale;
		singles[singleCount].textureOffset = textureOffset;

		singleCount++;
	}

	void move(int level)
	{
		if ((staticPipeline.level[level].block[dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y)] != 39
			&& staticPipeline.level[level].block[dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y)] != 'K'
			&& staticPipeline.level[level].block[dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y)] != '&'
			&& staticPipeline.level[level].block[dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y)] != '%'
			) || dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y) == dogPipeline.findBlockNo(singles[1].position.x, singles[1].position.y)
			&& staticPipeline.level[level].block[dogPipeline.findBlockNo(singles[0].position.x, singles[0].position.y)] < 127)
		{
			switch (roll(0, 1))
			{
			case 0:
				direction.x += 0.5;
				break;
			case 1:
				direction.x -= 0.5;
				break;
			default:
				break;
			}

			direction = glm::normalize(direction);

			direction *= -1;
		}

		//std::cout << dogPipeline.findBlockNo(0, 0) << "\n";
		singles[0].position += direction;
	}

	void render()
	{
		for (int i = 0; i < singleCount; i++)
		{
			modelLocation = glGetUniformLocation(program, "model");
			perspectiveLocation = glGetUniformLocation(program, "perspective");
			glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

			glBindTexture(GL_TEXTURE_2D, texture[singles[i].textureOffset]);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(singles[i].position, 0.0));
			model *= glm::scale(glm::mat4(1.0f), glm::vec3(singles[i].scale, 0));

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
};