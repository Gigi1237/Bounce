#ifndef WORLD_H
#define WORLD_H

#include "..\Fade2D\Fade2D.h"
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"

#define DEFAULT_TEXTURE "default.png"

class World
{
public:
	World();
	World(IFade2D* lib, std::string xmlPath, std::string texturePath);
	void addObject(IEntity* object);
	void draw();
	~World();
private:
	std::vector<IEntity*> worldObjects;
	IEntity *player;
};

#endif