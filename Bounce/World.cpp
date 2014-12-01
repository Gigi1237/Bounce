#include "World.h"
#include <iostream>
#include <cstdlib>

World::World(IFade2D* lib, std::string xmlPath, std::string texturePath)
{
	using namespace rapidxml;
	rapidxml::file<> xmlFile(xmlPath.c_str());
	xml_document<> xml;
	xml.parse<parse_declaration_node | parse_no_data_nodes>(xmlFile.data());

	std::cout << xml.first_node()->first_attribute("encoding")->value();

	xml_node<> *world = xml.first_node("world");
	xml_node<> *gameObject = world->first_node("Object");

	while (gameObject != NULL)
	{
		if ((gameObject->first_attribute("enabled") == NULL ? true : (bool)(atoi(gameObject->first_attribute("enabled")->value()))))
		{
			xml_node<> *position = gameObject->first_node("position");
			xml_node<> *size = gameObject->first_node("size");
			xml_node<> *texture = gameObject->first_node("texture");

			//Check if size and position nodes exist
			if (position != NULL && size != NULL){
				float posx = (float)atof(getNodeAttributeValue(position, "x"));
				float posy = (float)atof(getNodeAttributeValue(position, "y"));
				float sx = (float)atof(getNodeAttributeValue(size, "x"));
				float sy = (float)atof(getNodeAttributeValue(size, "y"));

				//Check if the size and position attributrs are not null
				if (posx != NULL && posy != NULL && sx != NULL && sy != NULL){
					if (texture != NULL)
					{
						std::string textureAttrib = texture->first_attribute("name")->value();
						worldObjects.push_back(Object(lib->newEntity(sx, sy, posx, posy, texturePath + textureAttrib)));
					}
					else
						worldObjects.push_back(Object(lib->newEntity(sx, sy, posx, posy, texturePath + DEFAULT_TEXTURE)));
				}
			}
		}
		gameObject = gameObject->next_sibling("Object");
	}
}

World::~World()
{
}

void World::addObject(Object object)
{
	worldObjects.push_back(object);
}

void World::draw()
{
	for each (Object object in worldObjects)
	{
		object.draw();
	}
}

char* getNodeAttributeValue(rapidxml::xml_node<> *node, std::string attributeName)
{
	using namespace rapidxml;
	xml_attribute<> *attrib = node->first_attribute(attributeName.c_str());

	if (attrib != NULL){
		if (attrib != NULL)
			return attrib->value();
		else
			return "";
	}
	else
		return "";
}