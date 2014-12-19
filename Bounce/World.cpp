#include "World.h"
#include <iostream>
#include <cstdlib>

World::World(IFade2D* lib) : lib(lib)
{
}

void World::loadFromXml(std::string xmlPath, std::string texturePath)
{
	using namespace rapidxml;
	rapidxml::file<> xmlFile(xmlPath.c_str());
	xml_document<> xml;
	xml.parse<parse_declaration_node | parse_no_data_nodes>(xmlFile.data());

	std::cout << xml.first_node()->first_attribute("encoding")->value();

	xml_node<> *world = xml.first_node("world");
	xml_node<> *gameObject = world->first_node("Background");
	bool end = false;

	while (gameObject != NULL)
	{
		if (getBoolAttribute(gameObject, "enabled", true)){
			xml_node<> *positionNode = gameObject->first_node("position");
			xml_node<> *sizeNode = gameObject->first_node("size");
			xml_node<> *textureNode = gameObject->first_node("texture");
			xml_node<> *angleNode = gameObject->first_node("angle");

			// Check if size and position nodes exist
			if (positionNode != NULL && sizeNode != NULL){
				vec2 position(getNodeAttributeValue(positionNode, "x"),
				getNodeAttributeValue(positionNode, "y"));
				vec2 size(getNodeAttributeValue(sizeNode, "x"),
				getNodeAttributeValue(sizeNode, "y"));
				float angle = angleNode != NULL ? (float)atof(angleNode->value()) : 0;
				std::string texture;

				// Check what texture to use
				if (textureNode != NULL)
					texture = texturePath + textureNode->first_attribute("name")->value();
				else
					texture = texturePath + DEFAULT_TEXTURE;

				if (std::string(gameObject->name()) == "Object")
					worldObjects.push_back(Object(lib, size, position, texture, angle));
				else if (std::string(gameObject->name()) == "PlayerObject")
					player = new PlayerObject(lib, size, position, texture, angle);
				else if (std::string(gameObject->name()) == "Background")
					background = new Background(lib, size, position, texture, angle);
			}
		}
		if (std::string(gameObject->name()) == "Background")
			gameObject = world->first_node("Object");
		else
			gameObject = gameObject->next_sibling("Object");

		if (gameObject == NULL && !end){
			gameObject = world->first_node("PlayerObject");
			end = true;
		}
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
	background->draw();
	for (auto &object : worldObjects){
		object.draw();
	}
	player->draw();
}

void World::update()
{
	player->update(vec2(0.f, 0.5f), worldObjects);
}

bool World::checkCollision(vec2 position, float radius)
{
	return false;
}

float getNodeAttributeValue(rapidxml::xml_node<> *node, std::string attributeName)
{
	using namespace rapidxml;
	xml_attribute<> *attrib = node->first_attribute(attributeName.c_str());

	if (attrib != NULL)
		return (float)atof(attrib->value());
	else
		return 0;
}

bool getBoolAttribute(rapidxml::xml_node<> *node, std::string attributeName, bool default)
{
	using namespace rapidxml;
	xml_attribute<> *attrib = node->first_attribute(attributeName.c_str());

	if (attrib != NULL){
		std::string value = attrib->value();
		if (value == "true")
			return true;
		else if (value == "false")
			return false;
		else
			return default;
	}
	else
		return default;
}

bool isOnScreen(vec2 windowSize, vec2 center)
{
	if (center.x < 0 || center.x > windowSize.x ||
		center.y < 0 || center.y > windowSize.y){
		return false;
	}
	return true;
}
