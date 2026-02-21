#pragma once

double xposOld = 0.0, yposOld = 0.0;
double xpos, ypos;
glm::vec3 currentLightPos;
glm::vec3 initalLightLoc = glm::vec3(5.0f, 2.0f, 2.0f);

void move()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera_pos += cameraN * (float)0.1 * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera_pos -= cameraU * (float)0.1 * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_pos -= cameraN * (float)0.1 * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_pos += cameraU * (float)0.1 * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera_pos += cameraV * (float)0.1 * 2.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera_pos -= cameraV * (float)0.1 * 2.0f;
	}

	glfwGetCursorPos(window, &xpos, &ypos);

	if (xposOld > xpos)
	{
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), -(float)(0.004 * (xposOld - xpos)), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraU = glm::vec4(cameraU, 0) * rMat;
		cameraV = glm::vec4(cameraV, 0) * rMat;
		cameraN = glm::vec4(cameraN, 0) * rMat;
	}
	if (xposOld < xpos)
	{
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), (float)(0.004 * (xpos - xposOld)), glm::vec3(0.0f, 1.0f, 0.0f));
		cameraU = glm::vec4(cameraU, 0) * rMat;
		cameraN = glm::vec4(cameraN, 0) * rMat;
		cameraV = glm::vec4(cameraV, 0) * rMat;
	}
	if (yposOld > ypos)
	{
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), -(float)(0.004 * (yposOld - ypos)), cameraU);
		cameraV = glm::vec4(cameraV, 0) * rMat;
		cameraN = glm::vec4(cameraN, 0) * rMat;

		glm::vec3 cameraV2 = glm::vec4(cameraV, 0) * rMat;
		glm::vec3 cameraN2 = glm::vec4(cameraN, 0) * rMat;
		if (cameraV.y < 0.0f)
		{
			cameraV = glm::vec4(cameraV, 0) / rMat;
			cameraN = glm::vec4(cameraN, 0) / rMat;
			cameraV.y = 0.0f;
			cameraV = glm::normalize(cameraV);
			cameraN.y = 1.0f;
			cameraN.x = 0.0f;
			cameraN.z = 0.0f;
			cameraU.y = 0.0f;
			cameraU = glm::normalize(cameraU);
		}
	}
	if (yposOld < ypos)
	{
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), (float)(0.004 * (ypos - yposOld)), cameraU);
		cameraV = glm::vec4(cameraV, 0) * rMat;
		cameraN = glm::vec4(cameraN, 0) * rMat;
		if (cameraV.y < 0.0f)
		{
			cameraV = glm::vec4(cameraV, 0) / rMat;
			cameraN = glm::vec4(cameraN, 0) / rMat;
			cameraV.y = 0.0f;
			cameraV = glm::normalize(cameraV);
			cameraN.y = -1.0f;
			cameraN.x = 0.0f;
			cameraN.z = 0.0f;
			cameraU.y = 0.0f;
			cameraU = glm::normalize(cameraU);
		}
	}

	xposOld = xpos;
	yposOld = ypos;
}