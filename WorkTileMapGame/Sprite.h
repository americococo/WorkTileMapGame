#pragma once

#include <vector>

#include <d3dx9.h>

class Frame;
class Texture;

class Sprite
{
private:
	//Frame * _frame;
	std::vector<Frame*> _frameList;
	int _currentFrame;


	//DirextX
private:
	
	// IDirect3DTexture9* _texture;
	RECT srcTextureRect;
	D3DCOLOR _texturecolor;
	//D3DXIMAGE_INFO textureInfo;
	
	LPDIRECT3DDEVICE9 _dirext3dDevice;
	LPD3DXSPRITE _sprite;

	LPCWSTR _textureFileName;
	LPCWSTR _scriptFileName;

public:

	Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName,float rotate=0.0f);
	~Sprite();


	void Init();

	void Init(int srcX,int srcY,int width,int height ,float delay);

	void deInit();
	
	void Release();
	void Reset();

	void Update(float deltaTime);
	void render();

	void setPostition(float posX,float posY);


private:
	float _x;
	float _y;
	float _rotate;

private:
	float _frameTime;

private:
	Texture * _srcTexture;



public:
	int GetWidth();
	int Getheight();
};