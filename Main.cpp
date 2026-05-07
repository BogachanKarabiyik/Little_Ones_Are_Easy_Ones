int level = 0;
#include "Includes.h"

bool breadAtHand = false;
GLFWwindow* window;
using namespace std::chrono_literals;
auto startTime = std::chrono::steady_clock::now();
auto now = std::chrono::steady_clock::now();
auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
int windowX = 0, windowY = 0;
int mousePress = -1;
int state = 0;
int selectedBlock = -1;
glm::vec2 ropePos = glm::vec2(-400, 0);
void readTxt(uint8_t levelNo)
{
	std::string line;
	std::string aaa;
	if (levelNo == 0)
		aaa = "Saves/one.txt";
	else if (levelNo == 1)
		aaa = "Saves/two.txt";
	else
		aaa = "Saves/three.txt";
	std::ifstream MyReadFile(aaa);

	uint8_t lineCounter = 0;
	while (std::getline(MyReadFile, line))
	{
		if (lineCounter == 18 && line != ".")
		{
			std::vector<std::string> result = staticPipeline.splitByComma(line);
			dogPipeline.allDogs[0].position.x = std::stoi(result[0]);
			dogPipeline.allDogs[0].position.y = std::stoi(result[1]);
			dogPipeline.allDogs[0].state = walkingRight;
			//dogPipeline.allDogs[0].bought = true;
		}
		else if (lineCounter == 19 && line != ".")
		{
			std::vector<std::string> result = staticPipeline.splitByComma(line);
			dogPipeline.allDogs[1].position.x = std::stoi(result[0]);
			dogPipeline.allDogs[1].position.y = std::stoi(result[1]);
			dogPipeline.allDogs[1].state = walkingRight;
			//dogPipeline.allDogs[1].bought = true;
		}
		else if (lineCounter == 20 && line != ".")
		{
			std::vector<std::string> result = staticPipeline.splitByComma(line);
			dogPipeline.allDogs[2].position.x = std::stoi(result[0]);
			dogPipeline.allDogs[2].position.y = std::stoi(result[1]);
			dogPipeline.allDogs[2].state = walkingRight;
			//dogPipeline.allDogs[2].bought = true;
		}
		else if (lineCounter == 21 && line != ".")
		{
			std::vector<std::string> result = staticPipeline.splitByComma(line);
			dogPipeline.allDogs[3].position.x = std::stoi(result[0]);
			dogPipeline.allDogs[3].position.y = std::stoi(result[1]);
			dogPipeline.allDogs[3].state = walkingRight;
			//dogPipeline.allDogs[3].bought = true;
		}
		else if (lineCounter == 22 && line != ".")
		{
			std::vector<std::string> result = staticPipeline.splitByComma(line);
			dogPipeline.allDogs[4].position.x = std::stoi(result[0]);
			dogPipeline.allDogs[4].position.y = std::stoi(result[1]);
			dogPipeline.allDogs[4].state = walkingRight;
			//dogPipeline.allDogs[4].bought = true;
		}

		for (int i = 0; i < 16 && lineCounter < 18; i++)
		{
			staticPipeline.level[levelNo].block[i + (16 * lineCounter)] = line[i];
		}
		lineCounter++;
	}

	MyReadFile.close();
}

bool once1 = false;
bool once2 = false;

bool once3 = false;
void renderState()
{
	if (state == 1)
	{
		glUseProgram(staticPipeline.program);
		staticPipeline.render(level);
		
		if (true)
		{
			for (int i = 0; i < 5; i++)
			{
				if (dogPipeline.allDogs[i].bought)
				{
					continue;
				}
				else
				{
					dogPipeline.allDogs[i].state = sittingRight;
					dogPipeline.allDogs[i].position.x = 10000;
					dogPipeline.allDogs[i].position.y = 10000;
				}
			}
			once2 = true;
		}

		glUseProgram(dogPipeline.program);
		dogPipeline.render();
		singlePipeline.singles[2].position = glm::vec2(10000, 10000);
		singlePipeline.singles[3].position = glm::vec2(10000, 10000);
		glUseProgram(textPipeline.program);
		textPipeline.render();

		glUseProgram(singlePipeline.program);
		singlePipeline.render();

		if (breadAtHand)
		{
			glUseProgram(menuPipeline.breadProgram);
			menuPipeline.renderBread();
		}

	}
	else if (state == 0)
	{
		float newGameX = -((((5 * 32) * 2) / 3) / 2);
		float length = std::abs(newGameX * 2);
		if (!once1)
		{
			textPipeline.addWriting("Start", 32, glm::vec3(1, 1, 1), glm::vec2(newGameX, 100));
			textPipeline.addWriting("13", 32, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
			once1 = true;
		}
		if (newGameX < mouseXWorld && newGameX + length > mouseXWorld &&
			100 < mouseYWorld && 132 > mouseYWorld)
		{
			textPipeline.changeWriting("Start", 32, glm::vec3(1, 0.5, 0.5), glm::vec2(newGameX, 100), 12);
			
			int mst = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			if (mst == GLFW_PRESS)
			{
				state = 1;
				once1 = false;
			}
		}
		else
		{
			textPipeline.changeWriting("Start", 32, glm::vec3(1, 1, 1), glm::vec2(newGameX, 100), 12);
		}
		glUseProgram(textPipeline.program);
		textPipeline.render();
	}
	else if (state == 2)
	{
		once2 = false;
		if (!once1)
		{
			dogPipeline.addDog(collie, glm::vec2(-660, 200));
			dogPipeline.addDog(husky, glm::vec2(-660, 100));
			dogPipeline.addDog(corgi, glm::vec2(-660, 0));
			dogPipeline.addDog(dalmation, glm::vec2(-660, -100));
			dogPipeline.addDog(labrador, glm::vec2(-660, -200));
			once1 = true;
		}

		menuPipeline.menu[0].position = glm::vec2(-640, -360);
		menuPipeline.menu[1].position = glm::vec2(10000, 10000);

		for (int i = 0; i < 5; i++)
		{
			if (!dogPipeline.allDogs[i].bought)
			{
				switch (i)
				{
				case 0:
					dogPipeline.allDogs[i].position = glm::vec2(-660, 200);
					break;
				case 1:
					dogPipeline.allDogs[i].position = glm::vec2(-660, 100);
					break;
				case 2:
					dogPipeline.allDogs[i].position = glm::vec2(-660, 0);
					break;
				case 3:
					dogPipeline.allDogs[i].position = glm::vec2(-660, -100);
					break;
				case 4:
					dogPipeline.allDogs[i].position = glm::vec2(-660, -200);
					break;
				default:
					break;
				}
			}
		}

		float X = -((((4 * 32) * 2) / 3) / 2);
		float Y = 320;

		textPipeline.changeWriting("Dogs", 32, glm::vec3(0.5, 1, 0.5), glm::vec2(X, Y), 12);
		singlePipeline.singles[2].position = glm::vec2(10000, 10000);
		singlePipeline.singles[3].position = glm::vec2(10000, 10000);
		glUseProgram(staticPipeline.program);
		staticPipeline.render(level);

		glUseProgram(menuPipeline.program);
		menuPipeline.render();

		glUseProgram(dogPipeline.program);
		dogPipeline.render();

		glUseProgram(textPipeline.program);
		textPipeline.render();

		glUseProgram(singlePipeline.program);
		singlePipeline.render();

		if (breadAtHand)
		{
			glUseProgram(menuPipeline.breadProgram);
			menuPipeline.renderBread();
		}
	}

	else if (state == 3)
	{
		if (!once3)
		{
			once3 = true;
		}

		menuPipeline.menu[0].position = glm::vec2(10000, 10000);
		menuPipeline.menu[1].position = glm::vec2(580, -360);

		float X = -((((5 * 32) * 2) / 3) / 2) + 320;
		float Y = 320;
		textPipeline.changeWriting("Decor", 32, glm::vec3(0.5, 1, 0.5), glm::vec2(X, Y), 13);

		singlePipeline.singles[2].position = glm::vec2(590, -350);
		singlePipeline.singles[3].position = glm::vec2(610, -350);

		glUseProgram(staticPipeline.program);
		staticPipeline.render(level);

		if (true)
		{
			for (int i = 0; i < 5; i++)
			{
				if (dogPipeline.allDogs[i].bought)
				{
					continue;
				}
				else
				{
					dogPipeline.allDogs[i].state = sittingRight;
					dogPipeline.allDogs[i].position.x = 10000;
					dogPipeline.allDogs[i].position.y = 10000;
				}
			}
			once2 = true;
		}

		glUseProgram(menuPipeline.program);
		menuPipeline.render();

		glUseProgram(dogPipeline.program);
		dogPipeline.render();

		glUseProgram(textPipeline.program);
		textPipeline.render();

		glUseProgram(singlePipeline.program);
		singlePipeline.render();

		if (breadAtHand)
		{
			glUseProgram(menuPipeline.breadProgram);
			menuPipeline.renderBread();
		}
	}
}

void render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glClear(GL_DEPTH_BUFFER_BIT);
	glm::vec3 a = glm::normalize(glm::vec3(149.0f, 160.0f, 131.0f));
	if (level == 0)
		glClearColor(a.x, a.y, a.z, 0.0f);
	else if (level == 1)
		glClearColor(0.61, 0.4, 0.33, 0.0);
	else
		glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDrawBuffer(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	renderState();

}
int aa = 0;
int ab = 0;
int ac = 0;
int ad = 0;
int ae = 0;
void playerLogic()
{
	while (true)
	{
		if (state != 0)
		{
			if (dogPipeline.allDogs[0].state != sittingRight)
			{
				if (dogPipeline.allDogs[0].hp.size())
					dogPipeline.allDogs[0].hp.pop_back();
				else
				{
					if (level != 2)
					{
						dogPipeline.allDogs[0].position = glm::vec2(10000, 100000);
						aa = 1;
					}
					else if (level == 2 && aa == 1)
					{
						aa = 0;
						dogPipeline.allDogs[0].position = glm::vec2(0, 0);
					}
				}

				staticPipeline.modifyLineInFile("Saves/one.txt", 19,
					std::to_string((int)dogPipeline.allDogs[0].position.x) + "." + std::to_string((int)dogPipeline.allDogs[0].position.y));
			}
			if (dogPipeline.allDogs[1].state != sittingRight)
			{
				if (dogPipeline.allDogs[1].hp.size())
					dogPipeline.allDogs[1].hp.pop_back();
				else
				{
					if (level != 2)
					{
						dogPipeline.allDogs[1].position = glm::vec2(10000, 100000);
						ab = 1;
					}
					else if (level == 2 && ab == 1)
					{
						ab = 0;
						dogPipeline.allDogs[1].position = glm::vec2(200, 0);
					}
				}

				staticPipeline.modifyLineInFile("Saves/one.txt", 20,
					std::to_string((int)dogPipeline.allDogs[1].position.x) + "." + std::to_string((int)dogPipeline.allDogs[1].position.y));
			}
			if (dogPipeline.allDogs[2].state != sittingRight)
			{
				if (dogPipeline.allDogs[2].hp.size())
					dogPipeline.allDogs[2].hp.pop_back();
				else
				{
					if (level != 2)
					{
						dogPipeline.allDogs[2].position = glm::vec2(10000, 100000);
						ac = 1;
					}
					else if (level == 2 && ac == 1)
					{
						ac = 0;
						dogPipeline.allDogs[2].position = glm::vec2(400, 0);
					}
				}

				staticPipeline.modifyLineInFile("Saves/one.txt", 21,
					std::to_string((int)dogPipeline.allDogs[2].position.x) + "." + std::to_string((int)dogPipeline.allDogs[2].position.y));
			}
			if (dogPipeline.allDogs[3].state != sittingRight)
			{
				if (dogPipeline.allDogs[3].hp.size())
					dogPipeline.allDogs[3].hp.pop_back();
				else
				{
					if (level != 2)
					{
						dogPipeline.allDogs[3].position = glm::vec2(10000, 100000);
						ad = 1;
					}
					else if (level == 2 && ad == 1)
					{
						ad = 0;
						dogPipeline.allDogs[3].position = glm::vec2(-200, 0);
					}
				}

				staticPipeline.modifyLineInFile("Saves/one.txt", 22,
					std::to_string((int)dogPipeline.allDogs[3].position.x) + "." + std::to_string((int)dogPipeline.allDogs[3].position.y));
			}
			if (dogPipeline.allDogs[4].state != sittingRight)
			{
				if (dogPipeline.allDogs[4].hp.size())
					dogPipeline.allDogs[4].hp.pop_back();
				else
				{
					if (level != 2)
					{
						dogPipeline.allDogs[4].position = glm::vec2(10000, 100000);
						ae = 1;
					}
					else if (level == 2 && ae == 1)
					{
						ae = 0;
						dogPipeline.allDogs[4].position = glm::vec2(-400, 0);
					}
				}

				staticPipeline.modifyLineInFile("Saves/one.txt", 23,
					std::to_string((int)dogPipeline.allDogs[4].position.x) + "." + std::to_string((int)dogPipeline.allDogs[4].position.y));
			}
			dogPipeline.updateRoll(staticPipeline);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		dogPipeline.pls = false;
	}
}

void npcLogic()
{
	while (true)
	{
		/*for (int i = 0; i < dogPipeline.dogCount; i++)
		{
			if (dogPipeline.allDogs[i].state == sittingLeft || dogPipeline.allDogs[i].state == sittingRight)
			{
				dogPipeline.allDogs[i].desiredPosition = dogPipeline.allDogs[i].position;
				continue;
			}

			dogPipeline.allDogs[i].desiredPosition.x = singlePipeline.singles[0].position.x;
			dogPipeline.allDogs[i].desiredPosition.y = singlePipeline.singles[0].position.y;
		}*/
		dogPipeline.update(staticPipeline);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void quickLogic()
{
	while (true)
	{
		singlePipeline.move(level);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

bool toggleDogToMouse = false;
int selectedDog = 0;

void handleMousePress()
{
	if (mousePress == 0)
	{
		glm::vec2 m = glm::vec2(mouseXWorld, mouseYWorld);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 35; j++)
			{
				if (m.x >= 589 + (i * 20) && m.x < 609 + (i * 20))
				{
					if (m.y <= 349 - (j * 20) && m.y > 329 - (j * 20))
					{
						selectedBlock = (i * 35) + j;
					}
				}
			}
		}

		if (selectedBlock != -1 && state == 3 && moneys >= 5)
		{
			staticPipeline.level[level].block[dogPipeline.findBlockNo(mouseXWorld, mouseYWorld)] = selectedBlock + 35;
			moneys -= 5;
			ses6.play();
			ses6.replay();
		}

		if (toggleDogToMouse && state == 2)
		{
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
			toggleDogToMouse = false;
			moneys -= 500;
			ses6.play();
			ses6.replay();
			dogPipeline.allDogs[selectedDog].state = walkingRight;
			dogPipeline.allDogs[selectedDog].bought = true;
			return;
		}

		if (moneys < 5)
			return;

		if (breadAtHand)
		{
			if (dogPipeline.allDogs[0].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
				dogPipeline.allDogs[0].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
			{
				moneys -= 5;
				ses6.play();
				ses6.replay();
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
				dogPipeline.allDogs[0].hp += '*';
				breadAtHand = false;
			}
			else if (dogPipeline.allDogs[1].position.x > mouseXWorld - 150 && dogPipeline.allDogs[1].position.x < mouseXWorld - 50 &&
				dogPipeline.allDogs[1].position.y < mouseYWorld - 50 && dogPipeline.allDogs[1].position.y > mouseYWorld - 100)
			{
				moneys -= 5;
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
				dogPipeline.allDogs[1].hp += '*';
				breadAtHand = false;
			}
			else if (dogPipeline.allDogs[2].position.x > mouseXWorld - 150 && dogPipeline.allDogs[2].position.x < mouseXWorld - 50 &&
				dogPipeline.allDogs[2].position.y < mouseYWorld - 50 && dogPipeline.allDogs[2].position.y > mouseYWorld - 100)
			{
				moneys -= 5;
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
				dogPipeline.allDogs[2].hp += '*';
				breadAtHand = false;
			}
			else if (dogPipeline.allDogs[3].position.x > mouseXWorld - 150 && dogPipeline.allDogs[3].position.x < mouseXWorld - 50 &&
				dogPipeline.allDogs[3].position.y < mouseYWorld - 50 && dogPipeline.allDogs[3].position.y > mouseYWorld - 100)
			{
				moneys -= 5;
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
				dogPipeline.allDogs[3].hp += '*';
				breadAtHand = false;
			}
			else if (dogPipeline.allDogs[4].position.x > mouseXWorld - 150 && dogPipeline.allDogs[4].position.x < mouseXWorld - 50 &&
				dogPipeline.allDogs[4].position.y < mouseYWorld - 50 && dogPipeline.allDogs[4].position.y > mouseYWorld - 100)
			{
				moneys -= 5;
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
				dogPipeline.allDogs[4].hp += '*';
				breadAtHand = false;
			}
		
			for (int i = 0; i < 5; i++)
			{
				if (dogPipeline.allDogs[i].hp.size() > 6 && dogPipeline.allDogs[i].state == sittingRight)
					moneys += 250;
			}
		}

		if (moneys < 500 || state != 2)
			return;

		if (m.x > -620 && m.x < -520 && m.y > 250 && m.y < 300)
		{
			toggleDogToMouse = true;
			selectedDog = 0;
			dogPipeline.allDogs[selectedDog].bought = true;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 200 && m.y > 150)
		{
			toggleDogToMouse = true;
			selectedDog = 1;
			dogPipeline.allDogs[selectedDog].bought = true;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 100 && m.y > 50)
		{
			toggleDogToMouse = true;
			selectedDog = 2;
			dogPipeline.allDogs[selectedDog].bought = true;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 0 && m.y > -50)
		{
			toggleDogToMouse = true;
			selectedDog = 3;
			dogPipeline.allDogs[selectedDog].bought = true;
		}
		else if (m.x > -620 && m.x < -520 && m.y < -100 && m.y > -150)
		{
			toggleDogToMouse = true;
			selectedDog = 4;
			dogPipeline.allDogs[selectedDog].bought = true;
		}
	}
	else if (mousePress == 1 && !breadAtHand)
	{
		breadAtHand = true;
	}
	else if (mousePress == 1 && breadAtHand)
	{
		breadAtHand = false;
	}
}
int winX, winY;

void worldLogic()
{
	while (true)
	{
		for (int i = 0; i < 5; i++)
		{
			if (dogPipeline.allDogs[i].state == walkingRight)
			{
				if (dogPipeline.allDogs[i].position.x + 150 > ropePos.x &&
					dogPipeline.allDogs[i].position.x + 150 < ropePos.x + 20 &&
					dogPipeline.allDogs[i].position.y + 75 > ropePos.y - 30 &&
					dogPipeline.allDogs[i].position.y + 75 < ropePos.y + 30)
				{
					ropePos.x = dogPipeline.allDogs[i].position.x + 150;
					ropePos.y = dogPipeline.allDogs[i].position.y + 75;
				}
			}
			else if (dogPipeline.allDogs[i].state == walkingLeft)
			{
				if (dogPipeline.allDogs[i].position.x + 50 > ropePos.x &&
					dogPipeline.allDogs[i].position.x + 50 < ropePos.x + 20 &&
					dogPipeline.allDogs[i].position.y + 75 > ropePos.y - 30 &&
					dogPipeline.allDogs[i].position.y + 75 < ropePos.y + 30)
				{
					ropePos.x = dogPipeline.allDogs[i].position.x + 50;
					ropePos.y = dogPipeline.allDogs[i].position.y + 75;
				}
			}
		}

		// Use this for ticks
		if (mouseX == -10000)
			continue;

		double ratio = (double)windowHeight / (double)windowWidth;

		float xw = ((float)windowWidth / 1920.0) * (ratio / 0.5625);
		float xw2 = (float)windowWidth / 1920.0;
		float yh = ((float)windowHeight / 1080.0) * (0.5625 / ratio);
		float yh2 = (float)windowHeight / 1080.0;

		int mouseXWorldP = (int)(windowWidth / (1.501 * xw) - 639);
		int mouseXWorldP2 = (int)(windowWidth / (1.501 * xw2) - 639);

		int mouseYWorldP = (int)(windowHeight / (1.501 * yh) + 359);
		int mouseYWorldP2 = (int)(windowHeight / (1.501 * yh2) + 359);

		int offset = std::abs(mouseXWorldP - mouseXWorldP2);
		int offset2 = std::abs(mouseYWorldP - mouseYWorldP2);
		
		offset /= 2;
		offset2 /= 2;

		if (ratio < 0.5625)
		{
			offset2 = 0;
			yh = yh2;
		}
		else
		{
			offset = 0;
			xw = xw2;
		}

		int winXWorld = (int)(winX / 1.501);
		int winYWorld = (int)(-winY / 1.501);

		mouseXWorld = (int)(mouseX / (1.501 * xw) - 639 - offset);
		mouseYWorld = (int)(-mouseY / (1.501 * yh) + 359 + offset2);

		glm::vec4 m = glm::vec4(mouseXWorld, mouseYWorld, 0, 0);
		glm::mat4 m2 = glm::inverse(perspective);

		glm::vec4 m3 = m2 * m;

		m3.x /= windowWidth;
		m3.y /= windowHeight;

		handleMousePress();

		mousePress = -1;

		if (toggleDogToMouse)
		{
			dogPipeline.allDogs[selectedDog].position.x = mouseXWorld - 100;
			dogPipeline.allDogs[selectedDog].position.y = mouseYWorld - 75;
		}
		if (breadAtHand)
		{
			menuPipeline.breadPos = glm::vec3(mouseXWorld, mouseYWorld, 0);
		}
		textPipeline.changeWriting(std::to_string(offset) + "<>" + std::to_string(winXWorld) + ", " + std::to_string(winYWorld) + ": " + std::to_string(mouseXWorld) + ", " + std::to_string(mouseYWorld), 16, glm::vec3(0, 0, 1), glm::vec2(0, 200), 1);

		if (state != 0)
		{
			float X = -((((4 * 32) * 2) / 3) / 2);
			float L = std::abs(X * 2);
			float Y = 320;

			textPipeline.changeWriting("Dogs", 32, glm::vec3(1, 1, 1), glm::vec2(X, Y), 12);

			if (X < mouseXWorld && X + L > mouseXWorld && Y < mouseYWorld && Y+32 > mouseYWorld)
			{
				textPipeline.changeWriting("Dogs", 32, glm::vec3(1, 0.5, 0.5), glm::vec2(X, Y), 12);

				int mst = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				if (mst == GLFW_PRESS)
				{
					if (state != 2)
						state = 2;
					else
						state = 1;
				}
			}
			else
			{
				textPipeline.changeWriting("Dogs", 32, glm::vec3(1, 1, 1), glm::vec2(X, Y), 12);
			}

			X = -((((5 * 32) * 2) / 3) / 2) + 320;
			L = std::abs(X * 2);
			Y = 320;

			textPipeline.changeWriting("Decor", 32, glm::vec3(1, 1, 1), glm::vec2(X, Y), 13);

			if (X < mouseXWorld && X + L > mouseXWorld && Y < mouseYWorld && Y + 32 > mouseYWorld)
			{
				textPipeline.changeWriting("Decor", 32, glm::vec3(1, 0.5, 0.5), glm::vec2(X, Y), 13);

				int mst = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				if (mst == GLFW_PRESS)
				{
					if (state != 3)
						state = 3;
					else
						state = 1;
				}
			}
			else
			{
				textPipeline.changeWriting("Decor", 32, glm::vec3(1, 1, 1), glm::vec2(X, Y), 13);
			}

			X = -((((5 * 32) * 2) / 3) / 2) - 320;
			Y = 320;

			glfwGetWindowPos(window, &winX, &winY);

			textPipeline.changeWriting("$" + std::to_string(moneys), 32, glm::vec3(1, 1, 1), glm::vec2(X, Y), 0);
			textPipeline.changeWriting(std::to_string(winXWorld) + ", " + std::to_string(winYWorld) + ": " + std::to_string(mouseXWorld) + ", " + std::to_string(mouseYWorld), 16, glm::vec3(0, 0, 1), glm::vec2(0, 200), 1);
			textPipeline.changeWriting(dogPipeline.allDogs[0].name, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[0].position.x + 65, dogPipeline.allDogs[0].position.y + 120), 2);
			textPipeline.changeWriting(dogPipeline.allDogs[1].name, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[1].position.x + 65, dogPipeline.allDogs[1].position.y + 120), 3);
			textPipeline.changeWriting(dogPipeline.allDogs[2].name, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[2].position.x + 65, dogPipeline.allDogs[2].position.y + 120), 4);
			textPipeline.changeWriting(dogPipeline.allDogs[3].name, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[3].position.x + 65, dogPipeline.allDogs[3].position.y + 120), 5);
			textPipeline.changeWriting(dogPipeline.allDogs[4].name, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[4].position.x + 65, dogPipeline.allDogs[4].position.y + 120), 6);

			textPipeline.changeWriting(dogPipeline.allDogs[0].hp, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[0].position.x + 65, dogPipeline.allDogs[0].position.y + 100), 7);
			textPipeline.changeWriting(dogPipeline.allDogs[1].hp, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[1].position.x + 65, dogPipeline.allDogs[1].position.y + 100), 8);
			textPipeline.changeWriting(dogPipeline.allDogs[2].hp, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[2].position.x + 65, dogPipeline.allDogs[2].position.y + 100), 9);
			textPipeline.changeWriting(dogPipeline.allDogs[3].hp, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[3].position.x + 65, dogPipeline.allDogs[3].position.y + 100), 10);
			textPipeline.changeWriting(dogPipeline.allDogs[4].hp, 16, glm::vec3(1, 1, 1), glm::vec2(dogPipeline.allDogs[4].position.x + 65, dogPipeline.allDogs[4].position.y + 100), 11);
		
			singlePipeline.singles[4].position = ropePos;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mousePress = 0;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		mousePress = 1;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[0].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[0].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			if (dogPipeline.allDogs[0].hp.length() >= 5)
				dogPipeline.allDogs[0].state = sittingRight;
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[0].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[0].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			dogPipeline.allDogs[0].state = walkingRight;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[1].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[1].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			if (dogPipeline.allDogs[1].hp.length() >= 5)
				dogPipeline.allDogs[1].state = sittingRight;
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[1].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[1].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			dogPipeline.allDogs[1].state = walkingRight;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[2].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[2].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			if (dogPipeline.allDogs[2].hp.length() >= 5)
				dogPipeline.allDogs[2].state = sittingRight;
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[2].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[2].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			dogPipeline.allDogs[2].state = walkingRight;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[3].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[3].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			if (dogPipeline.allDogs[3].hp.length() >= 5)
				dogPipeline.allDogs[3].state = sittingRight;
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[3].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[3].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			dogPipeline.allDogs[3].state = walkingRight;
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[4].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[4].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			if (dogPipeline.allDogs[4].hp.length() >= 5)
				dogPipeline.allDogs[4].state = sittingRight;
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		if (dogPipeline.allDogs[4].position.x > mouseXWorld - 150 && dogPipeline.allDogs[0].position.x < mouseXWorld - 50 &&
			dogPipeline.allDogs[4].position.y < mouseYWorld - 50 && dogPipeline.allDogs[0].position.y > mouseYWorld - 100)
		{
			dogPipeline.allDogs[4].state = walkingRight;
		}
	}

	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (level == 0)
			staticPipeline.level[level].block[dogPipeline.findBlockNo(mouseXWorld, mouseYWorld)] = 0;
		else if (level == 1)
			staticPipeline.level[level].block[dogPipeline.findBlockNo(mouseXWorld, mouseYWorld)] = 1;
		else
			staticPipeline.level[level].block[dogPipeline.findBlockNo(mouseXWorld, mouseYWorld)] = 2;
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		level++;

		if (level == 3)
			level = 0;
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		for (int i = 0; i < 5; i++)
		{
			dogPipeline.allDogs[i].desiredPosition.x = mouseXWorld;
			dogPipeline.allDogs[i].desiredPosition.y = mouseYWorld;
		}
	}

}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	if (codepoint == 46)
		selectedDog = 88;
	dogPipeline.allDogs[selectedDog].name += codepoint;

}

int main(void)
{

	glfwInit();
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	window = glfwCreateWindow(1920, 1080, "Doggy", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1);
	windowReshapeCallback(window, 1280, 720);
	glfwSetWindowSizeCallback(window, windowReshapeCallback);
	init();
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	std::thread playerThread(playerLogic);
	playerThread.detach();
	std::thread npcThread(npcLogic);
	npcThread.detach();
	std::thread worldThread(worldLogic);
	worldThread.detach();
	std::thread quickThread(quickLogic);
	quickThread.detach();

	textPipeline.addWriting("", 24, glm::vec3(1, 1, 1), glm::vec2(0, 0));
	textPipeline.addWriting("", 16, glm::vec3(0, 0, 1), glm::vec2(0, 200));

	dogPipeline.allDogs[0].state = sittingRight;
	dogPipeline.allDogs[1].state = sittingRight;
	dogPipeline.allDogs[2].state = sittingRight;
	dogPipeline.allDogs[3].state = sittingRight;
	dogPipeline.allDogs[4].state = sittingRight;

	textPipeline.addWriting("Collie", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("Husky", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("Corgi", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("Dalmation", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("Labrador", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));

	textPipeline.addWriting("***", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("***", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("***", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("***", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));
	textPipeline.addWriting("***", 16, glm::vec3(1, 1, 1), glm::vec2(-10000, -10000));

	singlePipeline.addSingle(glm::vec2(0, 0), glm::vec2(20, 20), 0);
	singlePipeline.addSingle(glm::vec2(0, 0), glm::vec2(100, 50), 1);
	singlePipeline.addSingle(glm::vec2(590, -350), glm::vec2(20, 700), 2);
	singlePipeline.addSingle(glm::vec2(610, -350), glm::vec2(20, 700), 3);

	singlePipeline.addSingle(glm::vec2(-400, 0), glm::vec2(20, 60), 4);

	menuPipeline.addMenu(glm::vec3(1, 0.5, 0.5), glm::vec2(-640, -360), glm::vec2(160, 720));
	menuPipeline.addMenu(glm::vec3(1, 0.5, 0.5), glm::vec2(600, -360), glm::vec2(160, 720));

	readTxt(0);
	readTxt(1);
	readTxt(2);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	while (!glfwWindowShouldClose(window))
	{
		now = std::chrono::steady_clock::now();
		frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
		startTime = std::chrono::steady_clock::now();
		glfwGetCursorPos(window, &mouseX, &mouseY);
		glfwGetWindowPos(window, &windowX, &windowY);
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			singlePipeline.singles[1].position.y++;
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		{
			singlePipeline.singles[1].position.x--;
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		{
			singlePipeline.singles[1].position.y--;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			singlePipeline.singles[1].position.x++;
		}
		render();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}