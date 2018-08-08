#include <stdio.h>

#include "ResourceManager.h"


ResourceManager  * ResourceManager::Instance = NULL;

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{

}

ResourceManager * ResourceManager::GetInstance()
{
	if (Instance == NULL)
		Instance = new ResourceManager();

	return Instance;
}

Texture * ResourceManager::LoadTexture(std::wstring  spriteFileName)
{
	std::map<std::wstring, Texture*>::iterator itr = _textureMap.find(spriteFileName);
	if (itr != _textureMap.end())
	{
		return itr->second;
	}


	Texture * texture = new Texture();
	texture->Init(spriteFileName.c_str());

	_textureMap[spriteFileName] = texture;
	return texture;
		
}
std::vector<std::string> ResourceManager::LoadScript(std::wstring scriptFileName)
{
	std::map<std::wstring, std::vector<std::string>>::iterator itr = _scriptMap.find(scriptFileName);
	if (itr != _scriptMap.end())
	{
		return itr->second;
	}

	char record[1000];
	std::ifstream infile(scriptFileName);
	std::vector<std::string > _scriptList;
	while (!infile.eof())
	{
		infile.getline(record, 100);
		 _scriptList.push_back(record);
	}

	_scriptMap[scriptFileName] = _scriptList;

	return _scriptList;
}
