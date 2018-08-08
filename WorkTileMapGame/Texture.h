#pragma once

#include <d3dx9.h>

class Texture
{
private:
	IDirect3DTexture9* _texture;
	D3DXIMAGE_INFO textureInfo;

public:
	Texture();
	~Texture();

	void Init(LPCWSTR  spriteFileName);
	void deInit();
	void Release();

	IDirect3DTexture9* GetTextureDX();
};