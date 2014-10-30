#include "..\Fade2D\Fade2D.h"
#include <iostream>
#include <Windows.h>
//#include <chrono>

int main()
{
	IFade2D *graphics = new_IFade2d(800, 600, "test");

	float ver[] = {
		0.f, 100.0f, 0.0f,
		0.f, 0.0f, 0.0f,
		200.f, 100.0f, 0.0f,
		200.f, 0.f, 0.f,
	};

	IEntity* square = new_IEntity(ver, sizeof(ver));

	bool color = false;

	while (graphics->windowShouldClose())
	{
		graphics->prepareScene();
		square->Draw();
		graphics->swapBuffer();
	}

	return 0;
}