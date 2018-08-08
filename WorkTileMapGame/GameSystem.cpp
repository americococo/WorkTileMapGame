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

//������ �ڵ�, �̺�Ʈ,           �ΰ����Ӽ�(�̺�Ʈ���� �ٸ�)
LRESULT CALLBACK/*ȣ��Ծ�*/ WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
		if (VK_ESCAPE == wParam)//�̺�Ʈ�� �ΰ����� �Ӽ�
		{
			DestroyWindow(hwnd);//�ڿ��������־�߉�
		}
		GameSystem::GetInstance()->KeyDown(wParam);
		return 0;
	case WM_KEYUP:
		GameSystem::GetInstance()->KeyUp(wParam);
		return 0;

	case WM_DESTROY://�ڿ������ �߻�
		PostQuitMessage(0);//�������� ��û(WM_Quit) 
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

	//���ö���Ʈ(2d comtext)

	hr = D3DXCreateSprite(_direxct3Ddevice, &_sprite);
	if (FAILED(hr))
	{
		MessageBox(0, L"false", L"���ö���Ʈ ���� Filed", MB_OK);
		return false;
	}



	return true;
}

bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;//������ ���ν��� (�޼��� �޾ƿ� ó��) ��<ó���Ŵ� �� ����>
	wc.cbClsExtra = 0;//�߰� �޸� ����
	wc.cbWndExtra = 0;//�߰� �޸� ����
	wc.hInstance = hInstance;//���� app�� �ڵ��� ����

	wc.hIcon = LoadIcon(0, IDI_APPLICATION);//������
	wc.hCursor = LoadCursor(0, IDC_ARROW);//Ŀ��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ȭ�� ����
	wc.lpszMenuName = 0;//�Ŵ�
	wc.lpszClassName = L"Base";//�������� �̸�

	if (!RegisterClass(&wc))
		return false;

	//���������� �����ϸ� �ڵ�޾ƿ�
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
		//Ŭ���̾�Ʈ ���� ������
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		int addwidth = clientWidth - clientRect.right;
		int addheigth = clientheight - clientRect.bottom;

		int finalwidth = clientWidth + addwidth;
		int finalheigth = clientheight + addheigth;

		MoveWindow(hWnd, 0, 0, finalwidth, finalheigth, TRUE);
	}

	//��¹� ������Ʈ
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (false == initDirect3D())
	{
		MessageBox(0, L"false", L"�ʱ�ȭ Filed", MB_OK);
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

	while (WM_QUIT != msg.message)//���������� ��� ����
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))//����� �޼���ť�� �ý����� �ڿ� �ʿ�� ����
		{
			//������ ó��(����ó���� �޼��� �߻��� ����)
			TranslateMessage(&msg);//�޼��� 
			DispatchMessage(&msg);//�޼��� ���޹���		
		}
		else
		{
			//�÷��� �Ի�
			gameTime->update();
			float deltaTime = gameTime->GetDeltaTime();


			//componentSystem->Update �޼���ť

			SceneManager::GetInstance()->Update(deltaTime);

			frameDuration += deltaTime;
			//���� ����




			if (secperFrame <= frameDuration)//�ϳ��� �÷��� ��������
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

