#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

glm::vec3 cameraU = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 cameraV = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraN = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);

struct Solid_Object
{
	glm::vec3 location = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	float angle = 0.0;
	glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 rotate2 = glm::vec3(0.0f, 0.0f, 1.0f);
	GLuint perspective_location, model_location, view_location, color_location, normal_location;
	glm::mat4 model, view;
	bool turn = false;
	int wait = 0;
	long long start = 0;
	int number = 0;

	void calcVmat()
	{
		glm::mat4 cameraRotation = glm::mat4(cameraU.x, cameraV.x, -cameraN.x, 0.0f,
			cameraU.y, cameraV.y, -cameraN.y, 0.0f,
			cameraU.z, cameraV.z, -cameraN.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 cameraTranslationMat = glm::mat4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			-camera_pos.x, -camera_pos.y, -camera_pos.z, 1.f);

		view = cameraRotation * cameraTranslationMat;

		model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::translate(glm::mat4(1.0f), location);

		model *= glm::scale(glm::mat4(1.0f), scale);
	}

	Solid_Object()
	{
		model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::translate(glm::mat4(1.0f), location);
		model *= glm::scale(glm::mat4(1.0f), scale);
		calcVmat();
	}
};