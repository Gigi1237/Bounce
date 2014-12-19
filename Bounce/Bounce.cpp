#include "Bounce.h"

int main()
{
	IFade2D *graphics = new_IFade2d(1280, 720, "Bounce!");
	World world(graphics);
	world.loadFromXml(XML_PATH"world.xml", TEXTURE_PATH);

	//Object obj(graphics->newEntity(100, 100, 600, 300, TEXTURE_PATH"default.png"), false, circular);


	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world.update();
		world.draw();
		////player->draw();
		////player->rotate(0.05);
		graphics->swapBuffer();
	}
}