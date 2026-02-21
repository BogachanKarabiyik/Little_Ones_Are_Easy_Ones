#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>

GLFWwindow* window;
glm::mat4 p_mat;
GLuint writing_sp;
GLuint obj_sp;
GLuint font_tex;
GLuint p_loc, camera_loc;
GLuint vao[1];
GLuint vbo[2];

#include "Writing.h"
#include "Obj.h"
#include "Scene.h"
#include "Controls.h"
#include "Render.h"

std::string writing_vs = R"(
	#version 430

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec2 texture_coord;

	uniform mat4 model;
	uniform mat4 perspective;

	out vec2 texture_position;
	out flat uint offset;

	uniform vec4 size_color;

	mat4 buildTranslate(float x, float y, float z)
	{
		mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
						  0.0, 1.0, 0.0, 0.0,
						  0.0, 0.0, 1.0, 0.0,
						  x,   y,   z,   1.0);
		return trans;
	}

	void main(void)
	{
		offset = gl_InstanceID;
		texture_position = texture_coord;

		mat4 next_model = buildTranslate(offset * (size_color.x * 0.666666666),0,0);
		next_model = next_model * model;
		gl_Position = perspective * next_model * vec4(position, 1.0);
	}
)";

std::string writing_fs = R"(
	#version 430

	out vec4 color;

	in vec2 texture_position;
	in flat uint offset;

	uniform uint writing[100];

	layout (binding=0) uniform sampler2D fragment_texture;

	uniform vec4 size_color;

	void main(void)
	{
		uint texture_offset = 0;

		if (offset - int(offset/4) * 4 == 0)
			texture_offset = writing[int(offset * 0.25) + 1] >> 24;
		else if (offset - int(offset/4) * 4 == 1)
			texture_offset = writing[int(offset * 0.25) + 1] >> 16 & 255;
		else if (offset - int(offset/4) * 4 == 2)
			texture_offset = writing[int(offset * 0.25) + 1] >> 8 & 255;
		else
			texture_offset = writing[int(offset * 0.25) + 1] & 255;

		vec4 texture_color = texture(fragment_texture, vec2((texture_position.x / 95) + 0.010526 * texture_offset, texture_position.y));

		color = texture_color * vec4(size_color.y, size_color.z, size_color.w, 1.0);
	}
)";

std::string obj_vs = R"(
	#version 430
	
	layout (location=0) in vec3 position;
	layout (location=1) in vec3 normal;
	out vec4 varyingColor;
	
	uniform mat4 m_matrix;
	uniform mat4 v_matrix;
	uniform mat4 p_matrix;
	
	mat4 buildTranslate(float x, float y, float z)
	{
		mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
						  0.0, 1.0, 0.0, 0.0,
						  0.0, 0.0, 1.0, 0.0,
						  x,   y,   z,   1.0);
		return trans;
	}
	
	struct PositionalLight
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec3 position;
	};
	
	struct Material
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
	};
	
	uniform vec4 globalAmbient;
	uniform PositionalLight light;
	uniform Material material;
	uniform mat4 norm_matrix;
	
	void main(void)
	{
		vec4 color;
	
		vec4 P = m_matrix * vec4(position, 1.0);
		vec3 N = normalize((norm_matrix * vec4(normal, 1.0)).xyz);	
		vec3 L = normalize(light.position - P.xyz);
	
		vec3 V = normalize(-v_matrix[3].xyz - P.xyz);
		vec3 R = reflect(-L,N);
	
		vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
		vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L),0.0);
		vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,V), 0.0f), material.shininess);
	
		varyingColor = vec4((ambient + diffuse + specular), 1.0);
	
		gl_Position = p_matrix * v_matrix * m_matrix * vec4(position, 1.0);
	}
)";

std::string obj_fs = R"(
	#version 430

	out vec4 color;
	uniform vec3 in_color;
	in vec4 varyingColor;

	struct PositionalLight
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		vec3 position;
	};

	struct Material
	{
		vec4 ambient;
		vec4 diffuse;
		vec4 specular;
		float shininess;
	};

	void main(void)
	{
		color = varyingColor;
	}
)";