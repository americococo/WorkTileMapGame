#pragma once
#include <d3dx9.h>
#include <string>
class Font
{
private:
	ID3DXFont * _dxFont;
	D3DCOLOR _color;
	std::wstring _text;

	int _x, _y;
	int _width, _height;

public:
	Font(std::wstring fontName,int size , D3DCOLOR color);
	~Font();

	void render();
	void SetRect(int x,int y,int width,int height);
	void setPosition(int x, int y);
	void setText(std::wstring text);
	

};
