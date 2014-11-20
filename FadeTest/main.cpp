#include "..\Fade2D\Fade2D.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

#define RES_X 1280
#define RES_Y 720

int main()
{
	IFade2D *graphics = new_IFade2d(RES_X, RES_Y, "test");


	IEntity* square = graphics->newEntity(100.f, 100.f, RES_X / 2, RES_Y / 2);
	//IEntity* square1 = new_IEntity(500.f, 100.f, 100.f, 200.f);
	
	//square->move(RES_X / 2, RES_Y / 2);
	//std::cout << square->getPosition()[0] << " AND " <<  square->getPosition()[1] << std::endl;

	clock_t t;

	//square->move(100.f, -200.f);


	bool color = false;
	float moveY = 0.f;
	float moveX = 0;
	float acc = 0.005f; //0.005f is a decent value
	t = clock();


	
	//while (graphics->windowShouldClose())
	//{
	//	// 521, 522
	//	graphics->prepareScene();
	//	if (clock() > t/(CLOCKS_PER_SEC / 60))
	//	{
	//		t = clock();
	//		moveY += acc;
	//		if ((0 > square->getPosition()[1] + moveY && moveY < 0) || (square->getPosition()[1] + moveY + 100 > RES_Y) && moveY > 0){
	//			if (moveY > 0)
	//			 moveY *= -0.83;
	//		}
	//		if ((0 > square->getPosition()[0] + moveX && moveX < 0) || (square->getPosition()[0] + moveX + 100 > RES_X) && moveX > 0){
	//			moveX *= -1;
	//		}
	//		square->move(moveX, moveY);
	//		if (GetAsyncKeyState(0x52)){
	//			square->move(0, -square->getPosition()[1]);
	//			moveY = 0;
	//		}
	//	}
	//	square->Draw();
	//	//square1->Draw();
	//	graphics->swapBuffer();
	//	//std::cout << square->getPosition()[0] << " AND " << square->getPosition()[1] << std::endl;
	//	//Sleep(1000);
	//}
	
	
	while (graphics->windowShouldClose())
	{
		graphics->prepareScene();
		square->rotate(0.1f);
		square->move(0.1f, 0.f);
		square->draw();
		graphics->swapBuffer();
	} 
	return 0;
}