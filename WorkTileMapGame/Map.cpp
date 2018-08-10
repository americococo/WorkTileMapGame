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

						Position tileposition;
						tileposition.x = x;
						tileposition.y = row;
						TileCell* tilecell = new TileCell(tileposition);
						WCHAR componetName[256];
						wsprintf(componetName, L"MapData_layer1_%d_%d", line, x);

						TileObject * tileObject = new TileObject(componetName, _spriteList[index], tileposition, eTileLayer::TileLayer_GROUND);
						tileObject->setCanMove(true);
						tilecell->AddTileObject(tileObject);
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
				//맵데이터
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
							Position tileposition;
							tileposition.x = x;
							tileposition.y = row;
							TileObject * tileObject = new TileObject(componetName, _spriteList[index],tileposition,eTileLayer::TileLayer_MIDLLE);
							tileObject->setCanMove(false);
							tilecell->AddTileObject(tileObject);
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

	{
		SelfMoveObject * moveobject = new SelfMoveObject(L"player");
		Position tilePosition;
		tilePosition.x = 1;
		tilePosition.y = 1;
		moveobject->Init(1, tilePosition,eTileLayer::TileLayer_MIDLLE);
		_turnList.push_back(moveobject);
	}
	{
		SelfMoveObject * moveobject = new SelfMoveObject(L"player");
		Position tilePosition;
		tilePosition.x = 5;
		tilePosition.y = 2;
		moveobject->Init(4, tilePosition,eTileLayer::TileLayer_SKY);
		_turnList.push_back(moveobject);
	}

	initViewer(_tileMap[_width / 2 - 1][_height / 2 - 1]->GetTileObject(eTileLayer::TileLayer_GROUND));

	_turnCircle = _turnList.begin();
}

void Map::Update(float deltaTime)
{
	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//뷰어의 위치를 기준으로 시작 픽셀 위치를 계산
	_startX = (-_viewer->GetTileX()*_tileSize) + midX - _tileSize / 2;
	_startY = (-_viewer->GetTileY()*_tileSize) + midY - _tileSize / 2;

	//해당위치에 타일그림
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

	SelfMoveObject * currentTurnOwner = (*_turnCircle);

	if (false == currentTurnOwner->IsActive())
	{
		_turnCircle++;
			
		if(_turnCircle== _turnList.end())
			_turnCircle = _turnList.begin();

		for (std::list<SelfMoveObject*>::iterator itr = _turnList.begin(); itr != _turnList.end(); itr++)
		{
			if (_turnCircle == itr)
				(*itr)->InitActivePoint();
			else
				(*itr)->ResetActivePoint();
		}
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
			delete _tileMap[y][x];
		}
	}
}

void Map::initViewer(TileObject * viewer)
{
	_viewer = viewer;

	//영역
	//최소x=뷰어의 현재 타일 x의 위치-(중심축의x좌표/타일 크기)-1 
	//최소y=뷰어의 현재 타일 y의 위치-(중심축의y좌표/타일 크기)-1
	//최대X=뷰어의 현재 타일 x의 위치+(중심축의x좌표/타일 크기)+1
	//최대y=뷰어의 현재 타일 y의 위치+(중심축의y좌표/타일 크기)+1

	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//뷰어의 위치를 기준으로 시작 픽셀 위치를 계산
	_startX = (-_viewer->GetTileX()*_tileSize) + midX - _tileSize / 2;
	_startY = (-_viewer->GetTileY()*_tileSize) + midY - _tileSize / 2;

	//해당위치에 타일그림
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			posX += _tileSize;
			_tileMap[y][x]->setPostition(posX, posY);
		}
		posX = _startX;
		posY += _tileSize;
	}

}
void Map::setTileComponent(Position tilePos, TileObject * tileobjet)
{
	_tileMap[tilePos.y][tilePos.x]->AddTileObject(tileobjet);
}

void Map::removeComponent(Position tileposition, TileObject * tileobjet)
{
	_tileMap[tileposition.y][tileposition.x]->removeComponent(tileobjet);
}
bool Map::CanMove(Position tilePosition,eTileLayer layer)
{
	return _tileMap[tilePosition.y][tilePosition.x]->CanMove(layer);
}