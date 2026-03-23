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

#include "Globals.h"
#include "Shaders.h"
#include "TextPipeline.h"
#include "StaticPipeline.h"
#include "DogPipeline.h"
#include "MenuPipeline.h"
#include "Utils.h"