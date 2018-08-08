#include "Frame.h"
#include "GameSystem.h"
#include "Texture.h"


Frame::Frame():_frameDelay(0.0f) {}
Frame::~Frame() {}

void Frame::Init( Texture * texture, int  x, int y, int Width, int height,float rotate, float frameDelay)
{
	_sprite = GameSystem::GetInstance()->getSprite();
	_texture = texture;

	_width = Width;
	_height = height;
	_rotate = rotate;
	srcTextureRect.left = x;
	srcTextureRect.top = y;
	srcTextureRect.right = _width + srcTextureRect.left;
	srcTextureRect.bottom = _height + srcTextureRect.top;

	_texturecolor = D3DCOLOR_ARGB(255, 255, 255, 255);

	_frameDelay = frameDelay;
}

void Frame::deInit()
{

}

void Frame::render()
{

	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(_width/ 2.0f,_height / 2.0f);
	D3DXVECTOR2 translate = D3DXVECTOR2(_x - ((float)_width / 2.0f), _y - (_height / 2.0f));
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);

	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&spriteCenter,
		_rotate,
		&translate
	);

	_sprite->SetTransform(&matrix);

	_sprite->Draw(_texture->GetTextureDX(), &srcTextureRect, NULL, NULL, _texturecolor);
}

void Frame::Release()
{

}

void Frame::Reset()
{

}

float Frame::GetFrameDelay()
{
	return _frameDelay;
}

void Frame::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}