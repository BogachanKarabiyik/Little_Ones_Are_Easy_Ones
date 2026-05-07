#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Audio/Sound.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <random>
#include <cstdio>
#include <cerrno>
#include <cstring>

Audio::Sound ses0{ "./Sounds/Dog/0.ogg" };
Audio::Sound ses1{ "./Sounds/Dog/1.ogg" };
Audio::Sound ses2{ "./Sounds/Dog/2.ogg" };
Audio::Sound ses3{ "./Sounds/Dog/3.ogg" };
Audio::Sound ses4{ "./Sounds/Dog/4.ogg" };
Audio::Sound ses5{ "./Sounds/Dog/5.ogg" };
Audio::Sound ses6{ "./Sounds/Dog/handleCoins.ogg" };

#include "Globals.h"
#include "Shaders.h"
#include "TextPipeline.h"
#include "StaticPipeline.h"
#include "DogPipeline.h"
#include "MenuPipeline.h"
TextPipeline textPipeline;
DogPipeline dogPipeline;
StaticPipeline staticPipeline;
MenuPipeline menuPipeline;
int mouseXWorld = 0, mouseYWorld = 0;
#include "SinglePipeline.h"
SinglePipeline singlePipeline;

#include "Utils.h"