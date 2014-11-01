#include "..\Fade2D\Fade2D.h"
#include <iostream>
#include <Windows.h>

#define RES_X 1280
#define RES_Y 720

int main()
{
	IFade2D *graphics = new_IFade2d(RES_X, RES_Y, "test");


	IEntity* square = new_IEntity(100.f, 200.f, RES_X / 2, RES_Y / 2);
	IEntity* square1 = new_IEntity(500.f, 100.f, 0, 0);
	
	//square->move(RES_X / 2, RES_Y / 2);
	//std::cout << square->getPosition()[0] << " AND " <<  square->getPosition()[1] << std::endl;
	bool color = false;
	float moveY = 0.125f;
	float moveX = 0.2f;

	while (graphics->windowShouldClose())
	{
		// 521, 522
		graphics->prepareScene();
		if ((0 > square->getPosition()[1]+moveY && moveY < 0) || (square->getPosition()[1]+moveY+200 > RES_Y) && moveY > 0){
			moveY *= -1;
		}
		if ((0 > square->getPosition()[0]+moveX && moveX < 0) || (square->getPosition()[0] + moveX + 100 > RES_X) && moveX > 0){
			moveX *= -1;
		}
		square->move(moveX, moveY);
		square->Draw();
		square1->Draw();
		graphics->swapBuffer();
		//std::cout << square->getPosition()[0] << " AND " << square->getPosition()[1] << std::endl;
		//Sleep(1000);
	}

	return 0;
}