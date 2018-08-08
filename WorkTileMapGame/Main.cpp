#include <Windows.h>
#include <time.h>
#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance/*현재 인스턴스 핸들*/, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow/*어떻게 보여줄지*/)
{
	srand(time(NULL));

	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);

	return GameSystem::GetInstance()->Update();
}
