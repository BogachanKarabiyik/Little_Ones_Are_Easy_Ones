#pragma once
#include "Includes.h"
int roll(int start, int end);

enum dogBreeds
{
	collie = 0,
	corgi,
	dalmation,
	husky,
	labrador
};

std::string dogNames[5] = { "Collie", "Corgi", "Dalmation", "Husky", "labrador" };

enum dogState
{
	sittingLeft = 0,
	sittingRight,
	walkingLeft,
	walkingRight,
	standingLeft,
	standingRight
};

struct Dog
{
	glm::vec2 position;
	uint8_t breed;
	GLint dogFrame = 1;
	glm::vec2 desiredPosition;
	uint8_t state = walkingRight;
	std::string name;
	std::string hp = "***";
};

struct DogPipeline
{
	GLuint program;
	GLuint perspectiveLocation, modelLocation, dogFrameLocation;
	
	glm::mat4 model;

	GLuint texture[5];

	Dog allDogs[100];

	uint8_t dogCount = 0;

	void addDog(uint8_t breed, glm::vec2 position)
	{
		allDogs[dogCount].breed = breed;
		allDogs[dogCount].position = position;
		allDogs[dogCount].name = "";

		dogCount++;
	}

	void render()
	{
		modelLocation = glGetUniformLocation(program, "model");
		dogFrameLocation = glGetUniformLocation(program, "dogFrame");
		perspectiveLocation = glGetUniformLocation(program, "perspective");
		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

		for (int i = 0; i < dogCount; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texture[allDogs[i].breed]);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(allDogs[i].position, 0.f));
			model *= glm::scale(glm::mat4(1.0f), glm::vec3(200.f, 200.f, 0.f));

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glUniform1i(dogFrameLocation, allDogs[i].dogFrame);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	int findBlockNo(int roll1, int roll2)
	{
		for (int b = 0; b < 18; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				if (roll1 > -640 + (80 * a) && roll1 < -560 + (80 * a) && roll2 < 360 - (40 * b) && roll2 > 320 - (40 * b))
				{
					return (b * 16) + a;
				}
			}
		}

		return 288;
	}
	
	glm::vec2 dogWidth(glm::vec2 pos)
	{
		glm::vec2 out;
		out.x = pos.x + 100;
		out.y = pos.y + 100;

		return out;
	}

	void updateRoll(StaticPipeline& s)
	{
		for (int i = 0; i < dogCount; i++)
		{
			if (allDogs[i].state == sittingLeft || allDogs[i].state == sittingRight)
			{
				allDogs[i].desiredPosition = allDogs[i].position;
				continue;
			}

			do
			{
				allDogs[i].desiredPosition.x = roll(-639, 639);
				allDogs[i].desiredPosition.y = roll(-359, 359);
			} while (s.level[0].block[findBlockNo(allDogs[i].desiredPosition.x, allDogs[i].desiredPosition.y)] == '#');
		}
	}

	void update(StaticPipeline& s)
	{
		for (int i = 0; i < dogCount; i++)
		{
			/*for (int j = i; j < dogCount; j++)
			{
				if (allDogs[i].position.y < allDogs[j].position.y)
				{
					Dog dog = allDogs[i];
					allDogs[i] = allDogs[j];
					allDogs[j] = dog;
				}
			}*/

			if (allDogs[i].state == walkingRight)
			{
				allDogs[i].dogFrame++;

				if (allDogs[i].dogFrame > 8 || allDogs[i].dogFrame < 1)
					allDogs[i].dogFrame = 1;
			}
			else if (allDogs[i].state == walkingLeft)
			{
				allDogs[i].dogFrame--;

				if (allDogs[i].dogFrame < -9 || allDogs[i].dogFrame > -2)
					allDogs[i].dogFrame = -2;
			}
			else if (allDogs[i].state == standingRight)
			{
				allDogs[i].dogFrame++;

				if (allDogs[i].dogFrame > 16 || allDogs[i].dogFrame < 9)
					allDogs[i].dogFrame = 9;
			}
			else if (allDogs[i].state == standingLeft)
			{
				allDogs[i].dogFrame--;

				if (allDogs[i].dogFrame < -17 || allDogs[i].dogFrame > -10)
					allDogs[i].dogFrame = -10;
			}
			else if (allDogs[i].state == sittingRight)
			{
				allDogs[i].dogFrame++;

				if (allDogs[i].dogFrame < 17)
					allDogs[i].dogFrame = 17;
				else if (allDogs[i].dogFrame > 22)
					allDogs[i].dogFrame = 22;
				continue;
			}
			else if (allDogs[i].state == sittingLeft)
			{
				allDogs[i].dogFrame--;

				if (allDogs[i].dogFrame > -18)
					allDogs[i].dogFrame = -18;
				else if (allDogs[i].dogFrame < -23)
					allDogs[i].dogFrame = -23;
				continue;
			}

			/*
			if (allDogs[i].dogFrame > 0)
			{
				allDogs[i].dogFrame++;

				if (allDogs[i].dogFrame >= 23)
					allDogs[i].dogFrame = -2;
			}
			else
			{
				allDogs[i].dogFrame--;

				if (allDogs[i].dogFrame <= -24)
					allDogs[i].dogFrame = 1;
			}
			*/

			if (allDogs[i].position != allDogs[i].desiredPosition)
			{
				glm::vec2 difference = allDogs[i].desiredPosition - allDogs[i].position;

				glm::vec2 dogW = dogWidth(allDogs[i].position);

				if (difference.x > 5 && s.level[0].block[findBlockNo(dogW.x + 5, dogW.y)] != '#')
				{
					allDogs[i].position.x += 5;
					allDogs[i].state = walkingRight;
				}
				else if (difference.x < 5 && difference.x > 0
					&& s.level[0].block[findBlockNo(dogW.x + 5, dogW.y)] != '#'
					&& s.level[0].block[findBlockNo(dogW.x + difference.x, dogW.y)] != '#')
				{
					allDogs[i].position.x += difference.x;
					allDogs[i].state = walkingRight;
				}
				else if (difference.y > 5 && s.level[0].block[findBlockNo(dogW.x, dogW.y + 5)] != '#')
				{
					allDogs[i].position.y += 5;
					allDogs[i].state = walkingRight;
				}
				else if (difference.y < 5 && difference.y > 0
					&& s.level[0].block[findBlockNo(dogW.x, dogW.y + 5)] != '#'
					&& s.level[0].block[findBlockNo(dogW.x, dogW.y + difference.y)] != '#')
				{
					allDogs[i].position.y += difference.y;
					allDogs[i].state = walkingRight;
				}
				else if (difference.x < 5 && s.level[0].block[findBlockNo(dogW.x - 5, dogW.y)] != '#')
				{
					allDogs[i].position.x -= 5;
					allDogs[i].state = walkingLeft;
				}
				else if (difference.x < 5 && difference.x != 0
					&& s.level[0].block[findBlockNo(dogW.x - 5, dogW.y)] != '#'
					&& s.level[0].block[findBlockNo(dogW.x - difference.x, dogW.y)] != '#')
				{
					allDogs[i].position.x -= difference.x;
					allDogs[i].state = walkingLeft;
				}
				else if (difference.y < 5 && s.level[0].block[findBlockNo(dogW.x, dogW.y - 5)] != '#')
				{
					allDogs[i].position.y -= 5;
					allDogs[i].state = walkingLeft;
				}
				else if (difference.y < 5 && difference.y != 0
					&& s.level[0].block[findBlockNo(dogW.x, dogW.y - 5)] != '#'
					&& s.level[0].block[findBlockNo(dogW.x, dogW.y - difference.y)] != '#')
				{
					allDogs[i].position.y -= difference.y;
					allDogs[i].state = walkingLeft;
				}
				else
				{
					if (allDogs[i].state == walkingLeft)
						allDogs[i].state = standingLeft;
					else if (allDogs[i].state == walkingRight)
						allDogs[i].state = standingRight;
				}
			}
			else
			{
				if (allDogs[i].state == walkingLeft)
					allDogs[i].state = standingLeft;
				else if (allDogs[i].state == walkingRight)
					allDogs[i].state = standingRight;
			}
		}
	}
};