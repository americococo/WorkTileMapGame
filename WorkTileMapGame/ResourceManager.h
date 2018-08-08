#pragma once
#include <d3dx9.h>
#include "Texture.h"//Resource메니저의 하위부품//

#include <string>
#include <map>
#include <vector>
#include <fstream>


class ResourceManager
{
private:
	static ResourceManager * Instance;

public:
	static ResourceManager * GetInstance();


public:
	Texture * LoadTexture(std::wstring  spriteFileName);

private:
	std::map<std::wstring, Texture*> _textureMap;

private:
	std::map < std::wstring, std::vector<std::string>> _scriptMap;

public:
	std::vector<std::string> LoadScript(std::wstring scriptFileName);
	
private:
	ResourceManager();
public:
	~ResourceManager();

};