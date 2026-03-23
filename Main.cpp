#include "Includes.h"

bool breadAtHand = false;

void render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glClear(GL_DEPTH_BUFFER_BIT);
	glm::vec3 a = glm::normalize(glm::vec3(149.0f, 160.0f, 131.0f));
	glClearColor(a.x, a.y, a.z, 0.0f);
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

	glUseProgram(staticPipeline.program);
	staticPipeline.render(0);

	glUseProgram(menuPipeline.program);
	menuPipeline.render();

	glUseProgram(dogPipeline.program);
	dogPipeline.render();

	glUseProgram(textPipeline.program);
	textPipeline.render();

	if (breadAtHand)
	{
		glUseProgram(menuPipeline.breadProgram);
		menuPipeline.renderBread();
	}
}
Audio::Sound ses0{ "./Sounds/Dog/0.ogg" };
Audio::Sound ses1{ "./Sounds/Dog/1.ogg" };
Audio::Sound ses2{ "./Sounds/Dog/2.ogg" };
Audio::Sound ses3{ "./Sounds/Dog/3.ogg" };
Audio::Sound ses4{ "./Sounds/Dog/4.ogg" };
Audio::Sound ses5{ "./Sounds/Dog/5.ogg" };

void playerLogic()
{
	while (true)
	{
		if (dogPipeline.allDogs[0].state != sittingRight)
		{
			if (dogPipeline.allDogs[0].hp.size())
				dogPipeline.allDogs[0].hp.pop_back();
			else
				dogPipeline.allDogs[0].position = glm::vec2(10000, 100000);
		}
		dogPipeline.updateRoll(staticPipeline);
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}
}

void npcLogic()
{
	while (true)
	{

		dogPipeline.update(staticPipeline);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int mousePress = -1;
bool toggleDogToMouse = false;
int selectedDog = 0;

void handleMousePress()
{
	if (mousePress == 0)
	{
		glm::vec2 m = glm::vec2(mouseXWorld, mouseYWorld);

		if (toggleDogToMouse)
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
			dogPipeline.allDogs[selectedDog].state = walkingRight;

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
		}

		if (moneys < 500)
			return;

		if (m.x > -620 && m.x < -520 && m.y > 250 && m.y < 300)
		{
			toggleDogToMouse = true;
			selectedDog = 0;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 200 && m.y > 150)
		{
			toggleDogToMouse = true;
			selectedDog = 1;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 100 && m.y > 50)
		{
			toggleDogToMouse = true;
			selectedDog = 2;
		}
		else if (m.x > -620 && m.x < -520 && m.y < 0 && m.y > -50)
		{
			toggleDogToMouse = true;
			selectedDog = 3;
		}
		else if (m.x > -620 && m.x < -520 && m.y < -100 && m.y > -150)
		{
			toggleDogToMouse = true;
			selectedDog = 4;
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

void worldLogic()
{
	while (true)
	{
		// Use this for ticks
		if (mouseX == -10000)
			continue;

		mouseXWorld = (int)(mouseX / 1.501 - 639);
		mouseYWorld = (int)(-mouseY / 1.501 + 359);

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

		textPipeline.changeWriting("$" + std::to_string(moneys), 24, glm::vec3(0.8, 0.8, 1.0), glm::vec2(-630, 320), 0);
		textPipeline.changeWriting(std::to_string(mouseXWorld) + ", " + std::to_string(mouseYWorld), 16, glm::vec3(0, 0, 1), glm::vec2(0, 2000), 1);
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
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	dogPipeline.allDogs[selectedDog].name += codepoint;
}

int main(void)
{
	GLFWwindow* window;
	
	glfwInit();
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
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

	textPipeline.addWriting("ewfergerwgerwgerwgrergh", 24, glm::vec3(1, 1, 1), glm::vec2(0, 0));
	textPipeline.addWriting("wrhrthjetwgerdsf", 16, glm::vec3(0, 0, 1), glm::vec2(0, 200));

	dogPipeline.addDog(collie, glm::vec2(-660, 200));
	dogPipeline.addDog(husky, glm::vec2(-660, 100));
	dogPipeline.addDog(corgi, glm::vec2(-660, 0));
	dogPipeline.addDog(dalmation, glm::vec2(-660, -100));
	dogPipeline.addDog(labrador, glm::vec2(-660, -200));

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

	staticPipeline.readTxt(0);

	menuPipeline.addMenu(glm::vec3(0.3, 0.2, 0.2), glm::vec2(-640, -360), glm::vec2(160, 720));
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	while (!glfwWindowShouldClose(window))
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);
		render();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}