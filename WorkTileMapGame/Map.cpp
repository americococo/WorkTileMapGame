#include "Map.h"
#include "Sprite.h"

#include "TileCell.h"
#include "TileObject.h"

#include "GameSystem.h"

#include "SelfMoveObject.h"

#include <fstream>

Map::Map(std::wstring name) :Component(name)
{
	_startX = _startY = 0.0f;
	_posX = _posY = 0.0f;
}

Map::~Map()
{

}
void Map::CreateMap_layer1()
{
	int srcX = 0;
	int srcY = 0;

	_height = 16;
	_width = 16;

	_tileSize = 32;


	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			Sprite * SpriteM = new Sprite(L"./Sprite/MapSprite/MapSprite.png", L"./Sprite/MapSprite/MapSprite.json");

			SpriteM->Init(srcX, srcY, _tileSize, _tileSize, 1.0f);
			_spriteList.push_back(SpriteM);

			srcX += _tileSize;
		}

		srcX = 0;
		srcY += _tileSize;
	}

	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layer01Name[256];
	sprintf(layer01Name, "./MapData/%s_MapData_layer1.csv", name.c_str());

	char layer02Name[256];
	sprintf(layer02Name, "./MapData/%s_MapData_layer2.csv", name.c_str());


	//1 layer load
	{
		int line = 0;
		int row = 0;
		char record[1024 * 4];
		std::ifstream infile(layer01Name);
		while (!infile.eof())
		{
			infile.getline(record, 1024 * 4);

			char *token = strtok(record, ",");
			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					_width = atoi(token);
					token = strtok(NULL, ",");
					_height = atoi(token);
				}
				break;
			case 1:
				break;
			default:
				if (NULL != token)
				{
					std::vector<TileCell*> rowList;
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);

						TileCell* tilecell = new TileCell(x, row);
						WCHAR componetName[256];
						wsprintf(componetName, L"MapData_layer1_%d_%d", line, x);

						TileObject * tileObject = new TileObject(componetName, _spriteList[index], x, row);

						tileObject->setCanMove(true);
						tilecell->AddComponent(tileObject);
						rowList.push_back(tilecell);
						token = strtok(NULL, ",");
					}
					_tileMap.push_back(rowList);
					row++;
				}
				break;
			}
			line++;
		}

	}
}
void Map::CreateMap_layer2()
{

	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layer02Name[256];
	sprintf(layer02Name, "./MapData/%s_MapData_layer2.csv", name.c_str());

	{
		int row = 0;
		int line = 0;
		char record[1024 * 4];
		std::ifstream infile(layer02Name);
		while (!infile.eof())
		{
			infile.getline(record, 1024 * 4);

			char *token = strtok(record, ",");
			switch (line)
			{
			case 0:
				break;
			case 1:
				break;

			default:
				//∏ µ•¿Ã≈Õ
				if (NULL != token)
				{
					std::vector<TileCell*> rowList = _tileMap[row];
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);

						if (0 <= index)
						{
							TileCell* tilecell = rowList[x];
							WCHAR componetName[256];
							wsprintf(componetName, L"MapData_layer2_%d_%d", line, x);
							TileObject * tileObject = new TileObject(componetName, _spriteList[index], x, row);
							tileObject->setCanMove(false);
							tilecell->AddComponent(tileObject);
						}

						token = strtok(NULL, ",");
					}
					row++;
				}
				break;
			}
			line++;
		}

	}
}
void Map::CreateMap()
{
	CreateMap_layer1();
	CreateMap_layer2();

}
void Map::Init()
{
	CreateMap();

	SelfMoveObject * moveobject = new SelfMoveObject(L"moveObject");
	moveobject->Init();
}

void Map::Update(float deltaTime)
{
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			posX += _tileSize;
			_tileMap[y][x]->setPostition(posX, posY);
			_tileMap[y][x]->Update(deltaTime);
		}
		posX = _startX;
		posY += _tileSize;
	}
}
void Map::render()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->render();
		}
	}
}
void Map::DeInit()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->DeInit();
		}
	}
}
