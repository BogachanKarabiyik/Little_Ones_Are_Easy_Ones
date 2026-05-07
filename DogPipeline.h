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
	bool bought = false;
};

struct DogPipeline
{
	GLuint program;
	GLuint perspectiveLocation, modelLocation, dogFrameLocation, levelLoc;
	
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
		levelLoc = glGetUniformLocation(program, "level");
		glUniformMatrix4fv(perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspective));

		for (int i = 0; i < dogCount; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texture[allDogs[i].breed]);

			model = glm::translate(glm::mat4(1.0f), glm::vec3(allDogs[i].position, 0.f));
			model *= glm::scale(glm::mat4(1.0f), glm::vec3(200.f, 200.f, 0.f));

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glUniform1i(dogFrameLocation, allDogs[i].dogFrame);
			glUniform1i(levelLoc, level);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

	int findBlockNo(int roll1, int roll2)
	{
		for (int b = 0; b < 18; b++)
		{
			for (int a = 0; a < 16; a++)
			{
				if (roll1 >= -640 + (80 * a) && roll1 <= -560 + (80 * a) && roll2 <= 360 - (40 * b) && roll2 >= 320 - (40 * b))
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
	int owned = 0;
	bool pls = false;

	int o1 = 65;
	int o2 = 85;
	void updateRoll(StaticPipeline& s)
	{
		for (int i = 0; i < dogCount; i++)
		{
			if (allDogs[i].state == sittingLeft || allDogs[i].state == sittingRight)
			{
				allDogs[i].desiredPosition = allDogs[i].position;
				continue;
			}

			for (int i = 0; i < 5; i++)
			{
				if (allDogs[i].bought)
					owned++;
			}

			int c = 0;

			if (owned > 1)
				c = roll(1, 1);

			if (c == 1)
			{
				int prev = 0;
				pls = true;
				for (int i = 0; i < 5; i++)
				{
					if (allDogs[i].bought)
					{
						allDogs[i].desiredPosition = allDogs[prev].position;
						prev = i;
						int r = roll(0, 5);
						if (r == 0)
							ses0.play();
						else if (r == 1)
							ses1.play();
						else if (r == 2)
							ses2.play();
						else if (r == 3)
							ses3.play();
						else if (r == 4)
							ses4.play();
						else
							ses5.play();
					}
				}
			}

			if (pls)
			{
				for (int i = 0; i < 5; i++)
				{
					if (allDogs[i].bought == true)
					{
						o1 = i;
						break;
					}
				}

				for (int i = o1 + 1; i < 5; i++)
				{
					if (allDogs[i].bought == true)
					{
						o2 = i;
						break;
					}
				}

				if (allDogs[o1].position.x < allDogs[o2].position.x)
				{
					allDogs[o1].desiredPosition.x = allDogs[o2].position.x - 75;
					allDogs[o2].desiredPosition.x = allDogs[o1].position.x + 75;
				}
				else
				{
					allDogs[o1].desiredPosition.x = allDogs[o2].position.x + 75;
					allDogs[o2].desiredPosition.x = allDogs[o1].position.x - 75;
				}

				allDogs[o1].desiredPosition.y = allDogs[o2].position.y;
				allDogs[o2].desiredPosition.y = allDogs[o1].position.y;

				int r = roll(0, 5);
				if (r == 0)
					ses0.play();
				else if (r == 1)
					ses1.play();
				else if (r == 2)
					ses2.play();
				else if (r == 3)
					ses3.play();
				else if (r == 4)
					ses4.play();
				else
					ses5.play();
			}

			do
			{
				allDogs[i].desiredPosition.x = roll(-639, 639);
				allDogs[i].desiredPosition.y = roll(-359, 359);
			} while (s.level[0].block[findBlockNo(allDogs[i].desiredPosition.x, allDogs[i].desiredPosition.y)] == '#');
		}
		owned = 0;
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
			for (int j = 0; j < dogCount; j++)
			{
				if (allDogs[i].position == allDogs[j].position && i != j)
				{
					return;
				}
			}
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