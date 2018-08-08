#include "Texture.h"
#include "GameSystem.h"
#include <d3dx9.h>

Texture::Texture() 
{
	_texture = NULL;
}
Texture::~Texture() {}

void Texture::Init(LPCWSTR  spriteFileName)
{
	HRESULT hr = D3DXGetImageInfoFromFile(spriteFileName, &textureInfo);
	if (FAILED(hr))
	{
		MessageBox(0, L"false", L"텍스쳐 정보 가져오기 Filed", MB_OK);
		return;
	}

	//가져온 폭 너비 정보로 텍스쳐 생성
	hr = D3DXCreateTextureFromFileEx(GameSystem::GetInstance()->getDevice()
		, spriteFileName
		, textureInfo.Width
		, textureInfo.Height
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_DEFAULT
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, D3DCOLOR_ARGB(255, 255, 255, 255)
		, &textureInfo
		, NULL
		, &_texture
	);
}
void Texture::deInit()
{
	RELEASE_COM(_texture);
}

void Texture::Release()
{

}


IDirect3DTexture9* Texture::GetTextureDX()
{
	return _texture;
}

