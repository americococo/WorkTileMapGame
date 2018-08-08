#pragma once
#include <d3dx9.h>

class Texture;

class Frame
{

private:
	Texture* _texture;
	LPD3DXSPRITE _sprite;
	RECT srcTextureRect;
	D3DCOLOR _texturecolor;

private:
	int _width;
	int _height;
	float _rotate;
public:
	Frame();
	~Frame();

	void Init(Texture * texture, int  x, int y, int Width, int height,float rotate, float frameDelay);
	void deInit();
	void render();
	void Reset();
	void Release();

	void SetPosition(float x,float y);

private:
	float _x;
	float _y;


private:
	float _frameDelay;

public:
	float GetFrameDelay();


	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
};