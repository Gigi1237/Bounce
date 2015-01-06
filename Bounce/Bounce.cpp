#include "Bounce.h"
#include <iostream>
#include <intrin.h>

World *world;

void ClearScreen()
{
    std::cout << std::string(100, '\n');
}

void handleUp(int action)
{
    //if (action == 1){
        ClearScreen();
        World::setGravity(World::getGravity() + 0.5f);
        std::cout << World::getGravity();
    //}
}

void handleDown(int action)
{
    //if (action == 1){
        ClearScreen();
        World::setGravity(World::getGravity() - 0.5f);
        std::cout << World::getGravity();
    //}
}

void handleSpace(int action)
{
    if (action == 1){
        world->loadFromXml(XML_PATH"world.xml", TEXTURE_PATH);
    }
}

int main()
{
    ClearScreen();
	IFade2D *graphics = new_IFade2d(1280, 720, "Bounce!");
	world = new World(graphics);
    World::setGravity(9.81f);
	world->loadFromXml(XML_PATH"world.xml", TEXTURE_PATH);

    graphics->setKeyPressHandler(up, &handleUp);
    graphics->setKeyPressHandler(down, &handleDown);
    graphics->setKeyPressHandler(space, &handleSpace);

    world->initClock();
	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world->update();
		world->draw();
		graphics->swapBuffer();
	}

    delete graphics;
    delete world;
    return 0;
}