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

	std::vector<std::string> splitByComma(const std::string& str) {
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;

		while (std::getline(ss, token, '.')) {
			tokens.push_back(token);
		}

		return tokens;
	}

    bool modifyLineInFile(const std::string& filename, int targetLine, const std::string& newText) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Could not open file '" << filename << "' for reading.\n";
            return false;
        }

        // Create a temporary file
        std::string tempFilename = filename + ".tmp";
        std::ofstream tempFile(tempFilename);
        if (!tempFile.is_open()) {
            std::cerr << "Error: Could not create temporary file.\n";
            inputFile.close();
            return false;
        }

        std::string currentLine;
        int currentLineNumber = 1;
        bool lineReplaced = false;

        // Read from the original file and write to the temp file
        while (std::getline(inputFile, currentLine)) {
            if (currentLineNumber == targetLine) {
                tempFile << newText << "\n";
                lineReplaced = true;
            }
            else {
                tempFile << currentLine << "\n";
            }
            currentLineNumber++;
        }

        // Close both files to release locks before deleting/renaming
        inputFile.clear();
        tempFile.clear();
        inputFile.close();
        tempFile.close();

        // If the line was never reached, clean up the temp file and return
        if (!lineReplaced) {
            std::cerr << "Error: Line " << targetLine << " is out of bounds.\n";
            std::remove(tempFilename.c_str());
            return false;
        }

        // Delete the original file
        if (std::remove(filename.c_str()) != 0) {
            std::cerr << "Error: Could not delete the original file.\n";
            perror("Reason");
            return false;
        }

        // Rename the temp file to the original file's name
        if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
            std::cerr << "Error: Could not rename the temporary file.\n";
            return false;
        }

        return true;
    }
};