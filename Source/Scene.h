#pragma once
#include "Writing.h"
#include "Obj.h"

int scene_count = 0;

struct Scene
{
	Writing* writing[100];
	Solid_Object* solid_object[100];

	int writing_count = 0;
	int solid_object_count = 0;
	Scene()
	{
		scene_count++;
	}

	void add_writing(Writing* object)
	{
		writing[writing_count] = object;
		writing_count++;
	}

	void add_solid_object(Solid_Object* object)
	{
		solid_object[solid_object_count] = object;
		solid_object_count++;
	}
};
