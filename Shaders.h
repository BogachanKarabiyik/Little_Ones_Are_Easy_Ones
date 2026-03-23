#pragma once
#include <string>

std::string textVertex = R"(
	#version 430

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec2 textureCoord;
	uniform mat4 model;
	uniform mat4 perspective;

	out vec2 texturePosition;
	out uint offset;

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
		texturePosition = textureCoord;
		gl_Position = perspective * (buildTranslate(offset * model[0][0] * 0.666666666,0,0) * model) * vec4(position, 1.0);
	}
)";

std::string textFragment = R"(
	#version 430

	out vec4 outColor;

	in vec2 texturePosition;
	in flat uint offset;

	uniform uint writing[100];
	uniform vec3 color;

	layout (binding=0) uniform sampler2D fragmentTexture;

	void main(void)
	{
		uint off = 0;

		if (offset - int(offset/4) * 4 == 0)
			off = writing[int(offset * 0.25) + 1] >> 24;
		else if (offset - int(offset/4) * 4 == 1)
			off = writing[int(offset * 0.25) + 1] >> 16 & 255;
		else if (offset - int(offset/4) * 4 == 2)
			off = writing[int(offset * 0.25) + 1] >> 8 & 255;
		else
			off = writing[int(offset * 0.25) + 1] & 255;
		vec4 textureColor = texture(fragmentTexture, vec2((texturePosition.x / 95) + 0.010526 * off, texturePosition.y));

		outColor = vec4(color, 1) * textureColor;
	}
)";

std::string dogVertex = R"(
	#version 430

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec2 textureCoord;

	uniform mat4 model;
	uniform mat4 perspective;

	out vec2 texturePosition;

	void main(void)
	{
		texturePosition = textureCoord;
		gl_Position = perspective * model * vec4(position, 1.0);
	}
)";

std::string dogFragment = R"(
	#version 430

	out vec4 outColor;

	in vec2 texturePosition;
	uniform int dogFrame;

	layout (binding=0) uniform sampler2D fragmentTexture;

	void main(void)
	{
		vec4 textureColor = texture(fragmentTexture, vec2((texturePosition.x / 23) + 0.043478 * dogFrame, texturePosition.y));
		outColor = textureColor;
	}
)";

std::string staticVertex = R"(
	#version 430

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec2 textureCoord;

	uniform mat4 model;
	uniform mat4 perspective;

	out vec2 texturePosition;
	out int offset;
	uniform uint level[288];

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
		texturePosition = textureCoord;
		offset = gl_InstanceID;
		int nextLine = 0;

		if (offset < 16)
			nextLine = 0;
		else if (offset < 32)
			nextLine = -1;
		else if (offset < 48)
			nextLine = -2;
		else if (offset < 64)
			nextLine = -3;
		else if (offset < 80)
			nextLine = -4;
		else if (offset < 96)
			nextLine = -5;
		else if (offset < 112)
			nextLine = -6;
		else if (offset < 128)
			nextLine = -7;
		else if (offset < 144)
			nextLine = -8;
		else if (offset < 160)
			nextLine = -9;
		else if (offset < 176)
			nextLine = -10;
		else if (offset < 192)
			nextLine = -11;
		else if (offset < 208)
			nextLine = -12;
		else if (offset < 224)
			nextLine = -13;
		else if (offset < 240)
			nextLine = -14;
		else if (offset < 256)
			nextLine = -15;
		else if (offset < 272)
			nextLine = -16;
		else
			nextLine = -17;

		mat4 newMatrix = buildTranslate(((15 - offset) + nextLine * -16) * 80, -17 - nextLine * 40, 0);

		gl_Position = perspective * (newMatrix * model) * vec4(position, 1.0);
	}
)";

std::string staticFragment = R"(
	#version 430

	out vec4 outColor;

	in vec2 texturePosition;
	in flat int offset;
	uniform uint level[288];

	layout (binding=0) uniform sampler2D fragmentTexture;

	void main(void)
	{
		vec4 textureColor;

		if (level[287 - offset] == 35)		
			textureColor = texture(fragmentTexture, vec2((texturePosition.x / 70) + 0.043478 * 0, texturePosition.y));
		else
			textureColor = texture(fragmentTexture, vec2((texturePosition.x / 70) + 0.043478 * 1, texturePosition.y));

		outColor = textureColor;
	}
)";

std::string menuVertex = R"(
	#version 430

	layout(location = 0) in vec3 position;

	uniform mat4 model;
	uniform mat4 perspective;

	void main(void)
	{
		gl_Position = perspective * model * vec4(position, 1.0);
	}
)";

std::string menuFragment = R"(
	#version 430

	out vec4 outColor;

	uniform vec3 color;

	void main(void)
	{
		outColor = vec4(color, 1);
	}
)";

std::string breadVertex = R"(
	#version 430

	layout(location = 0) in vec3 position;
	layout(location = 1) in vec2 textureCoord;

	uniform mat4 model;
	uniform mat4 perspective;

	out vec2 texturePosition;

	void main(void)
	{
		texturePosition = textureCoord;
		gl_Position = perspective * model * vec4(position, 1.0);
	}
)";

std::string breadFragment = R"(
	#version 430

	out vec4 outColor;

	in vec2 texturePosition;

	layout (binding=0) uniform sampler2D fragmentTexture;

	void main(void)
	{
		vec4 textureColor = texture(fragmentTexture, texturePosition);
		outColor = textureColor;
	}
)";