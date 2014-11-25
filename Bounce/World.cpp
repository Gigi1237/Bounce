#include "World.h"
#include <iostream>
#include <cstdlib>

World::World()
{
}

World::World(IFade2D* lib, std::string xmlPath, std::string texturePath)
{
	using namespace rapidxml;
	rapidxml::file<> xmlFile(xmlPath.c_str());
	xml_document<> xml;
	xml.parse<parse_declaration_node | parse_no_data_nodes>(xmlFile.data());

	std::cout << xml.first_node()->first_attribute("encoding")->value();

	xml_node<> *world = xml.first_node("world");
	xml_node<> *gameObject = world->first_node("gameObject");

	while (gameObject != NULL)
{
		xml_node<> *position = gameObject->first_node("position");
		xml_node<> *size = gameObject->first_node("size");
		xml_node<> *texture = gameObject->first_node("texture");
		if (position != NULL && size != NULL){
			float posx = (float)atof(position->first_attribute("x")->value());
			float posy = (float)atof(position->first_attribute("y")->value());
			float sx = (float)atof(size->first_attribute("x")->value());
			float sy = (float)atof(size->first_attribute("y")->value());
			if (texture != NULL)
			{
				std::string textureAttrib = texture->first_attribute("name")->value();
				worldObjects.push_back(lib->newEntity(sx, sy, posx, posy, texturePath + textureAttrib));
			}
			else
				worldObjects.push_back(lib->newEntity(sx, sy, posx, posy, texturePath+DEFAULT_TEXTURE));
		}
		gameObject = gameObject->next_sibling("gameObject");
	}
}

World::~World()
{
}

void World::addObject(IEntity* object)
{
	worldObjects.push_back(object);
}

void World::draw()
{
	for each (IEntity* object in worldObjects)
	{
		object->draw();
	}
}