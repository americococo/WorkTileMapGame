#include <Windows.h>
#include <time.h>
#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE hInstance/*���� �ν��Ͻ� �ڵ�*/, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow/*��� ��������*/)
{
	srand(time(NULL));

	GameSystem::GetInstance()->InitSystem(hInstance, nCmdShow);

	return GameSystem::GetInstance()->Update();
}
