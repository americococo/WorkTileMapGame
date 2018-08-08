#include "GameSystem.h"
#include "gameTimer.h"
#include "Font.h"
#include "Sprite.h"

#include <Windows.h>
#include <stdio.h>
#include <string>

#include "SceneManager.h"
#include "Scene.h"

GameSystem * GameSystem::_instance = 0;

#define KeySpeed 8.0f

//윈도우 핸들, 이벤트,           부가적속성(이벤트별로 다름)
LRESULT CALLBACK/*호출규약*/ WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int mouseX;
	int mouseY;


	switch (msg)
	{
	case WM_LBUTTONDOWN:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		GameSystem::GetInstance()->mouseDown(mouseX, mouseY);
		return 0;

	case WM_LBUTTONUP:
		GameSystem::GetInstance()->mouseUp();
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)//이벤트의 부가적인 속성
		{
			DestroyWindow(hwnd);//자원해제해주어야됌
		}
		GameSystem::GetInstance()->KeyDown(wParam);
		return 0;
	case WM_KEYUP:
		GameSystem::GetInstance()->KeyUp(wParam);
		return 0;

	case WM_DESTROY://자원종료시 발생
		PostQuitMessage(0);//정상종료 요청(WM_Quit) 
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
void GameSystem::mouseDown(int mouseX, int mouseY)
{
	_isMouseDown = true;
	_mouseX = mouseX;
	_mouseY = mouseY;
}


void GameSystem::mouseUp()
{
	_isMouseDown = false;
}
void GameSystem::KeyDown(unsigned int keycode)
{
	_keystate[keycode] = eKeyState::KEY_DOWN;
}
void GameSystem::KeyUp(unsigned int keycode)
{
	_keystate[keycode] = eKeyState::KEY_UP;
}

bool GameSystem::IsKeyDown(unsigned int keycode)
{
	return (eKeyState::KEY_DOWN == _keystate[keycode]);
}

void GameSystem::InitInput()
{
	for (int i = 0; i < 256; i++)
	{
		_keystate[i] = eKeyState::KEY_UP;
	}
	_isMouseDown = false;
}

GameSystem * GameSystem::GetInstance()
{
	if (_instance == 0)
		_instance = new GameSystem();

	return _instance;
}

GameSystem::GameSystem() :clientWidth(1024), clientheight(800)
{
	isFULLScreen = false;
}
GameSystem::~GameSystem()
{
	RELEASE_COM(_direxct3Ddevice);
	RELEASE_COM(_sprite);

}

bool GameSystem::initDirect3D()
{

	LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (NULL == direct3d)
	{
		MessageBox(0, L"false", L"create Filed", MB_OK);
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = clientWidth;
	d3dpp.BackBufferHeight = clientheight;

	if (isFULLScreen)
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = (!isFULLScreen);
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	HRESULT hr = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	DWORD behavior;
	if (FAILED(hr))
	{
		MessageBox(0, L"false", L"create Filed", MB_OK);
		return false;
	}

	if ((caps.DeviceType & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || (caps.VertexShaderVersion < D3DVS_VERSION(1, 1)))
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	else
	{
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, behavior, &d3dpp, &_direxct3Ddevice);

	//스플라이트(2d comtext)

	hr = D3DXCreateSprite(_direxct3Ddevice, &_sprite);
	if (FAILED(hr))
	{
		MessageBox(0, L"false", L"스플라이트 생성 Filed", MB_OK);
		return false;
	}



	return true;
}

bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;//윈도우 프로시저 (메세지 받아와 처리) ※<처리돼는 일 많음>
	wc.cbClsExtra = 0;//추가 메모리 슬릇
	wc.cbWndExtra = 0;//추가 메모리 슬릇
	wc.hInstance = hInstance;//현재 app와 핸들을 연결

	wc.hIcon = LoadIcon(0, IDI_APPLICATION);//아이콘
	wc.hCursor = LoadCursor(0, IDC_ARROW);//커서
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경화면 설정
	wc.lpszMenuName = 0;//매뉴
	wc.lpszClassName = L"Base";//윈도우의 이름

	if (!RegisterClass(&wc))
		return false;

	//성공적으로 생성하면 핸들받아옴
	DWORD style;
	if (isFULLScreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}

	hWnd = CreateWindow(
		L"Base",
		L"TitleName",
		style, 
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		clientWidth, 
		clientheight, 
		0,
		0, 
		hInstance, 
		0
	);

	if (0 == hWnd)
		return false;

	if (!isFULLScreen)
	{
		//클라이언트 영역 가져옴
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		int addwidth = clientWidth - clientRect.right;
		int addheigth = clientheight - clientRect.bottom;

		int finalwidth = clientWidth + addwidth;
		int finalheigth = clientheight + addheigth;

		MoveWindow(hWnd, 0, 0, finalwidth, finalheigth, TRUE);
	}

	//출력및 업데이트
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (false == initDirect3D())
	{
		MessageBox(0, L"false", L"초기화 Filed", MB_OK);
		return false;
	}


	SceneManager::GetInstance()->Init();
	SceneManager::GetInstance()->ChangeScene(eScene::SC_TITLE);

	return true;

}

int GameSystem::Update()
{
	MSG msg = { 0 };

	gameTimer * gameTime = new gameTimer();
	gameTime->Reset();

	float frameDuration = 0.0f;
	float secperFrame = 1.0f / 60;

	while (WM_QUIT != msg.message)//종료전까지 계속 돌림
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))//사용한 메세지큐를 시스템이 자원 필요시 삭제
		{
			//윈도우 처리(게임처리중 메세지 발생시 실행)
			TranslateMessage(&msg);//메세지 
			DispatchMessage(&msg);//메세지 전달받음		
		}
		else
		{
			//플레임 게산
			gameTime->update();
			float deltaTime = gameTime->GetDeltaTime();


			//componentSystem->Update 메세지큐

			SceneManager::GetInstance()->Update(deltaTime);

			frameDuration += deltaTime;
			//수정 요함




			if (secperFrame <= frameDuration)//하나의 플레임 지나갔음
			{


				_direxct3Ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0F, 0);
				{
					_direxct3Ddevice->BeginScene();
					{
						_sprite->Begin(D3DXSPRITE_ALPHABLEND);

						SceneManager::GetInstance()->render();

						_sprite->End();
					}
					_direxct3Ddevice->EndScene();
				}



				_direxct3Ddevice->Present(NULL, NULL, NULL, NULL);

				frameDuration = 0.0f;

			}

		}
	}
	return  (int)msg.wParam;

}



int GameSystem::GetWidth()
{
	return clientWidth;
}

int GameSystem::GetHeight()
{
	return clientheight;
}

LPD3DXSPRITE GameSystem::GetSprite()
{
	return _sprite;
}
LPDIRECT3DDEVICE9 GameSystem::GetDevice()
{
	return _direxct3Ddevice;
}

