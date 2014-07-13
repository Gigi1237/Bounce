#include "..\Fade2D\Fade2D.h"

int main()
{
	Fade2D graphics(800, 600, "test");

	GLfloat ver[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5, -0.5, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	GLfloat ver2[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-0.8f, -1.0f, 0.0f,
		-0.8f, 1.0f, 0.0f
	};

	Entity square(ver, sizeof(ver));
	Entity square1(ver2, sizeof(ver2));

	while (graphics.windowShouldClose())
	{
		square1.Draw(graphics);
		square.Draw(graphics);
		graphics.swapBuffer();
	}

	return 0;
}