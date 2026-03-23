#pragma once
#include "Includes.h"

TextPipeline textPipeline;
DogPipeline dogPipeline;
StaticPipeline staticPipeline;
MenuPipeline menuPipeline;
double mouseX = -10000, mouseY = 0;
int mouseXWorld = 0, mouseYWorld = 0;
int moneys = 1400;

int roll(int start, int end)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(start, end);
	return distribution(generator);
}

void printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

void printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

bool checkOpenGLError()
{
	bool foundError = 0;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

GLuint makeShaderProgram(std::string vertex, std::string fragment)
{
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	const char* vertexSource = vertex.c_str();
	const char* fragmentSource = fragment.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(vertexShader);
	checkOpenGLError();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		std::cout << "vertex compilation failed" << std::endl;
		printShaderLog(vertexShader);
	}

	glCompileShader(fragmentShader);
	checkOpenGLError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		std::cout << "fragment compilation failed" << std::endl;
		printShaderLog(fragmentShader);
	}

	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	checkOpenGLError();
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		printProgramLog(program);
	}

	return program;
}

void setupVertices()
{
	float square[18] =
	{
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	float texture[12] =
	{
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);
}

GLuint loadTexture(const char* path)
{
	GLuint textureID;
	textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0) std::cout << "Could not find texture file " << path << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	return textureID;
}

void init()
{
	textPipeline.program = makeShaderProgram(textVertex, textFragment);
	dogPipeline.program = makeShaderProgram(dogVertex, dogFragment);
	staticPipeline.program = makeShaderProgram(staticVertex, staticFragment);
	menuPipeline.program = makeShaderProgram(menuVertex, menuFragment);
	menuPipeline.breadProgram = makeShaderProgram(breadVertex, breadFragment);
	setupVertices();

	textPipeline.texture = loadTexture("Textures/Atlas.png");

	dogPipeline.texture[0] = loadTexture("Textures/Collie.png");
	dogPipeline.texture[1] = loadTexture("Textures/Corgi.png");
	dogPipeline.texture[2] = loadTexture("Textures/Dalmation.png");
	dogPipeline.texture[3] = loadTexture("Textures/Husky.png");
	dogPipeline.texture[4] = loadTexture("Textures/Labrador.png");

	staticPipeline.texture = loadTexture("Textures/Isometric.png");
	menuPipeline.texture = loadTexture("Textures/Blank.png");
	menuPipeline.bread = loadTexture("Textures/Bread.png");
}

void windowReshapeCallback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	perspective = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	float targetWidth = 1280.0f;
	float targetHeight = 720.0f;
	float A = targetWidth / targetHeight;
	float V = (float)width / (float)height;

	if (V >= A)
	{
		perspective = glm::ortho(-V / A * targetWidth / 2.0f, V / A * targetWidth / 2.0f, -targetHeight / 2.0f, targetHeight / 2.0f);
	}
	else
	{
		perspective = glm::ortho(-targetWidth / 2.0f, targetWidth / 2.0f, -A / V * targetHeight / 2.0f, A / V * targetHeight / 2.0f);
	}

}