#pragma once

#include "Object.h"
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"

#define DEFAULT_TEXTURE "default.png"
#define COLLISION_TEST_DIST 250

#include "Object.h"
#include "vec2.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Object;
class PlayerObject;
class Background;

class World
{
public:
	World(IFade2D* lib);
	void loadFromXml(std::string xmlPath, std::string texturePath);
	void addObject(Object object);
	void draw();
	void update();
	bool checkCollision(vec2 position, float radius);
	bool isOnScreen(vec2 center, vec2 size, float angle);
	~World();
private:
	std::vector<Object> worldObjects;
	PlayerObject* player;
	Background* background;
	IFade2D* lib;
};

float getNodeAttributeValue(rapidxml::xml_node<> *node, std::string attributeName);
bool getBoolAttribute(rapidxml::xml_node<> * node, std::string attributeName, bool default = false);
bool isOnScreen(vec2 windowSize, vec2 center);