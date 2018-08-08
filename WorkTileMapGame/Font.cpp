#include "Font.h"
#include "GameSystem.h"
Font::Font(std::wstring fontName, int size, D3DCOLOR color)
{
	_color = color;
	HRESULT hr = D3DXCreateFont(GameSystem::GetInstance()->getDevice(), size, 0, FW_HEAVY, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		fontName.c_str(), &_dxFont);

	if (FAILED(hr))
	{
		MessageBox(0, L"false", L"font Filed", MB_OK);
	}
}
Font::~Font()
{
	RELEASE_COM(_dxFont);
}
void Font::render()
{
	RECT rect;
	rect.left =_x;
	rect.top = _y;
	rect.right = _x + _width;
	rect.bottom = _y + _height;

	D3DXMATRIX martrix;
	D3DXMatrixTransformation2D(&martrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);
	GameSystem::GetInstance()->getSprite()->SetTransform(&martrix);
	_dxFont->DrawTextW(GameSystem::GetInstance()->getSprite(), _text.c_str(), -1, &rect, DT_CENTER, _color);
}
void Font::SetRect(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

}
void Font::setPosition(int x,int y)
{
	_x = x;
	_y = y;
}

void Font::setText(std::wstring text)
{
	_text = text;
}
