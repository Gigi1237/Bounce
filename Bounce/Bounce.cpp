#include "Bounce.h"

int main()
{
	IFade2D *graphics = new_IFade2d(1280, 720, "Bounce!");
	World world(graphics, XML_PATH"world.xml", TEXTURE_PATH);

	Object* player = new Object(graphics->newEntity(100, 100, 600, 300, TEXTURE_PATH"Platforms\\Potion_Bg_Blue.png"));

	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world.draw();
		player->draw();
		player->rotate(0.05);
		graphics->swapBuffer();
	}
}