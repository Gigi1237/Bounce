#include "Bounce.h"

int main()
{
	IFade2D *graphics = new_IFade2d(1280, 720, "Bounce!");
	World world(graphics);
	world.loadFromXml(XML_PATH"world.xml", TEXTURE_PATH);


	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world.update();
		world.draw();
		graphics->swapBuffer();
	}
}