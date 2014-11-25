#include "Bounce.h"

int main()
{
	IFade2D *graphics = new_IFade2d(800, 600, "Bounce!");
	World world(graphics, XML_PATH"world.xml", TEXTURE_PATH);

	IEntity* player = graphics->newEntity(100, 100, 600, 300, TEXTURE_PATH"rotation.png");

	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world.draw();
		player->draw();
		player->rotate(0.05);
		graphics->swapBuffer();
	}
}