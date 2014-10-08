#include "..\Fade2D\Fade2D.h"
#include <iostream>

int main()
{
	Fade2D *graphics = new_fade2d(800, 600, "test");

	float ver[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5, -0.5, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	float ver2[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-0.8f, -1.0f, 0.0f,
		-0.8f, 1.0f, 0.0f
	};

	Entity* square = new_entity(ver, sizeof(ver));
	//Entity square1(ver, sizeof(ver), graphics);

	//std::cout << square.getVboId();
	//std::cout << square1.getVboId();
	//system("PAUSE");

	while (graphics->windowShouldClose())
	{
	//	square1.Draw(graphics);
		square->Draw(graphics->getProgramId());
		graphics->swapBuffer();
	}

	return 0;
}