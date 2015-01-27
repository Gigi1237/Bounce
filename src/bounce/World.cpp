#include "World.h"
#include <iostream>
#include <cstdlib>

World::World(IFade2D* lib) : lib(lib)
{
	gravity = 9.81f / HEIGHT_OF_WINDOW_M;
	timeOfUpdate = clock();
}

void World::loadFromXml(std::string xmlPath, std::string texturePath)
{
	using namespace rapidxml;
	rapidxml::file<> xmlFile(xmlPath.c_str());
	xml_document<> xml;
	xml.parse<parse_declaration_node | parse_no_data_nodes>(xmlFile.data());


	xml_node<> *world = xml.first_node("world");
	xml_node<> *gameObject = world->first_node("Object");

	while (gameObject != NULL)
	{
		EntityData data = getEntityData(gameObject);
		if (data.enabled)
			worldObjects.push_back(Object(lib, data.Size, data.Position, texturePath + data.texture, data.angle));
		gameObject = gameObject->next_sibling("Object");
	}

	EntityData playerData = getEntityData(world->first_node("PlayerObject"));
	if (playerData.enabled)
		player = new PlayerObject(lib, playerData.Size, playerData.Position, texturePath + playerData.texture, playerData.angle);

	EntityData backGroundData = getEntityData(world->first_node("Background"));
	if (backGroundData.enabled)
		background = new Background(lib, backGroundData.Size, backGroundData.Position, texturePath + backGroundData.texture, backGroundData.angle);
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
	clock_t timeStep = (clock() - timeOfUpdate);
	player->update(vec2(0.f, gravity), (float)timeStep/CLOCKS_PER_SEC, worldObjects);
	timeOfUpdate = clock();
}

void World::setGravity(float g)
{
	gravity = g / HEIGHT_OF_WINDOW_M;
}

EntityData getEntityData(rapidxml::xml_node<> *node)
{
	using namespace rapidxml;
	EntityData data;
	if (getBoolAttribute(node, "enabled", true)){
		xml_node<> *positionNode = node->first_node("position");
		xml_node<> *sizeNode = node->first_node("size");
		xml_node<> *textureNode = node->first_node("texture");
		xml_node<> *angleNode = node->first_node("angle");

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
				texture = textureNode->first_attribute("name")->value();
			else
				texture = DEFAULT_TEXTURE;

			data.enabled = true;
			data.Size = size;
			data.Position = position;
			data.texture = texture;
			data.angle = angle;
			//if (std::string(node->name()) == "Object")
			//	worldObjects.push_back(Object(lib, size, position, texture, angle));
			//else if (std::string(gameObject->name()) == "PlayerObject")
			//	player = new PlayerObject(lib, size, position, texture, angle);
			//else if (std::string(gameObject->name()) == "Background")
			//	background = new Background(lib, size, position, texture, angle);
		}
		else
			data.enabled = false;
	}
	else
		data.enabled = false;

	return data;
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

bool getBoolAttribute(rapidxml::xml_node<> *node, std::string attributeName, bool defaultValue)
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
			return defaultValue;
	}
	else
		return defaultValue;
}

bool isOnScreen(vec2 windowSize, vec2 center)
{
	if (center.x < 0 || center.x > windowSize.x ||
		center.y < 0 || center.y > windowSize.y){
		return false;
	}
	return true;
}
