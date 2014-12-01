#ifndef WORLD_H
#define WORLD_H

#include "Object.h"
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"

#define DEFAULT_TEXTURE "default.png"

class World
{
public:
	World(IFade2D* lib, std::string xmlPath, std::string texturePath);
	void addObject(Object object);
	void draw();
	~World();
private:
	std::vector<Object> worldObjects;
	Object* player;
};

char* getNodeAttributeValue(rapidxml::xml_node<> *node, std::string attributeName);

#endif