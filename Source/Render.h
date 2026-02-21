#pragma once

void window_reshape_callback_writing(GLFWwindow* window, int width, int height);

void render(Scene& scene)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(writing_sp);


	window_reshape_callback_writing(window, 1280, 720);
	p_loc = glGetUniformLocation(writing_sp, "perspective");
	glUniformMatrix4fv(p_loc, 1, GL_FALSE, glm::value_ptr(p_mat));

	glActiveTexture(GL_TEXTURE0);

	// Render the writing
	glBindTexture(GL_TEXTURE_2D, font_tex);

	for (int i = 0; i < scene.writing_count; i++)
	{
		scene.writing[i]->model_loc = glGetUniformLocation(writing_sp, "model");
		scene.writing[i]->size_color_loc = glGetUniformLocation(writing_sp, "size_color");

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		scene.writing[i]->writing_loc = glGetUniformLocation(writing_sp, "writing");

		scene.writing[i]->update();

		glUniform1uiv(scene.writing[i]->writing_loc, 100, scene.writing[i]->writing);
		glUniformMatrix4fv(scene.writing[i]->model_loc, 1, GL_FALSE, glm::value_ptr(scene.writing[i]->model));
		glUniform4fv(scene.writing[i]->size_color_loc, 1, glm::value_ptr(scene.writing[i]->size_color));
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, scene.writing[i]->writing[0]);
	}

	// Render the objs
}