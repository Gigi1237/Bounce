#include "World.h"
#include <iostream>
#include <cstdlib>

World::World()
{
}

World::World(IFade2D* lib, std::string xmlPath)
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
		if (position != NULL && size != NULL){
			float posx = atof(position->first_attribute("x")->value());
			float posy = atof(position->first_attribute("y")->value());
			float sx = atof(size->first_attribute("x")->value());
			float sy = atof(size->first_attribute("y")->value());
			worldObjects.push_back(lib->newEntity(sx, sy, posx, posy));

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