#include "Bounce.h"

int main()
{
	IFade2D *graphics = new_IFade2d(800, 600, "Bounce!");
	World world(graphics, std::string(R"(D:\Users\Luigi\Documents\Visual Studio 2013\Projects\Fade2D\Bounce\world.xml)"));

	while (graphics->windowShouldClose()){
		graphics->prepareScene();
		world.draw();
		graphics->swapBuffer();
	}
}