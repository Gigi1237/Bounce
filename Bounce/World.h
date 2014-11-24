#pragma once

#include "Bounce.h"
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"

class World
{
public:
	World();
	World(IFade2D* lib, std::string xmlPath);
	void addObject(IEntity* object);
	void draw();
	~World();
private:
	std::vector<IEntity*> worldObjects;
	IEntity *player;
};

