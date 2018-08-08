#pragma once

#include <D3DX9.h>
#include <vector>
#include <list>

#define RELEASE_COM(x){if(x){x->Release();x=NULL;}}
class Stage;
class Component;

class GameSystem
{

private:
	static GameSystem * _instance;
public:
	static GameSystem * GetInstance();

	//window 등록,생성&출력
public:
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();



	//direct3d
private:

	//dirext 9
private:
	LPDIRECT3DDEVICE9 _direxct3Ddevice;
	LPD3DXSPRITE _sprite;
	D3DPRESENT_PARAMETERS d3dpp;
public:
	bool initDirect3D();

private:
	HWND hWnd;
	bool isFULLScreen;
	int clientWidth;
	int clientheight;

private:
	GameSystem();
public:
	~GameSystem();


	//텍스쳐
private:
	//std::list<Component*> _compoentList;
	Stage * _stage;


public:
	Stage * getStage() { return _stage; }
	//get
public:
	int GetWidth();
	int GetHeight();
	LPD3DXSPRITE getSprite();
	LPDIRECT3DDEVICE9 getDevice();

	//입력

public:
	enum eKeyState
	{
		KEY_DOWN, KEY_UP
	};

public:
	void KeyDown(unsigned int keycode);
	void KeyUp(unsigned int keycode);

	void InitInput();

private:
	bool _isMouseDown;
	int _mouseX;
	int _mouseY;

public:
	void mouseDown(int mouseX, int mouseY);
	void mouseUp();

	bool IsMouseDown() { return _isMouseDown; }
	int GetMouseX() { return _mouseX; }
	int GetMouseY() { return _mouseY; }

private:

	eKeyState _keystate[256];



public:
	bool IsKeyDown(unsigned int keycode);



};