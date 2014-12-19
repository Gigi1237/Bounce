#pragma once

#ifdef _DEBUG
#define XML_PATH "..\\Bounce\\"
#define TEXTURE_PATH "..\\Resources\\Textures\\"
#else
#define XML_PATH "Resources\\"
#define TEXTURE_PATH "Resources\\Textures\\"
#endif

#include <vector>
#include <fstream>
#include "World.h"
#include "Object.h"