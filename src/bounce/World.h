#pragma once

#include "Object.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#define DEFAULT_TEXTURE "default.png"
#define COLLISION_TEST_DIST 250

#include "Object.h"
#include "vec2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#define HEIGHT_OF_WINDOW_M 4.f

class Object;
class PlayerObject;
class Background;

struct EntityData
{
	vec2 Position;
	vec2 Size;
	std::string texture;
	float angle;
	bool enabled;
};

class World
{
public:
	World(IFade2D* lib);
	void loadFromXml(std::string xmlPath, std::string texturePath);
	void addObject(Object object);
	void draw();
	void update();
	bool isOnScreen(vec2 center, vec2 size, float angle);
	~World();
	void setGravity(float g);
private:
	std::vector<Object> worldObjects;
	PlayerObject* player;
	Background* background;
	IFade2D* lib;
	float gravity;
	clock_t timeOfUpdate;
};

float getNodeAttributeValue(rapidxml::xml_node<> *node, std::string attributeName);
bool getBoolAttribute(rapidxml::xml_node<> * node, std::string attributeName, bool defaultValue = false);
bool isOnScreen(vec2 windowSize, vec2 center);
EntityData getEntityData(rapidxml::xml_node<>* node);
