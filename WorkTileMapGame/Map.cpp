#include "Map.h"
#include "Sprite.h"

#include "TileCell.h"
#include "TileObject.h"

#include "GameSystem.h"

#include "SelfMoveObject.h"
#include "Player.h"
#include "Monster.h"
#include <fstream>

Map::Map(std::wstring name) :Component(name)
{
	_startX = _startY = 0.0f;
	_posX = _posY = 0.0f;

}

Map::~Map()
{

}
void Map::CreateMap_layer_Ground()
{

	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layer01Name[256];
	sprintf(layer01Name, "./MapData/%s_MapData_layer1.csv", name.c_str());



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
						wsprintf(componetName, L"MapData_layer%d_%d_%d", eTileLayer::TileLayer_GROUND +1 , line, x);

						TileObject * tileObject = new TileObject(componetName, _spriteList[index], tileposition, eTileLayer::TileLayer_GROUND);
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
		initViewer(_tileMap[_width / 2 - 1][_height / 2 - 1]->GetTileObject(eTileLayer::TileLayer_GROUND));
	}
}

void Map::CreateMap_layer(eTileLayer layer)
{

	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layername[256];
	sprintf(layername, "MapData_layer%d.csv", (int)layer+1);



	char layer01Name[256];
	sprintf(layer01Name, "./MapData/%s_", name.c_str());

	char layer02Name[256];
	sprintf(layer02Name, "%s%s",layer01Name,layername);

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
				//�ʵ�����
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
							wsprintf(componetName, L"MapData_layer%d_%d_%d",layer+1, line, x);
							Position tileposition;
							tileposition.x = x;
							tileposition.y = row;
							TileObject * tileObject = new TileObject(componetName, _spriteList[index],tileposition,layer);
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
	CreateMap_layer_Ground();
	CreateMap_layer(eTileLayer::TileLayer_MIDLLE);
}
void Map::Create_Component()
{
	std::wstring wName = _name;
	std::string name = "";
	name.assign(wName.begin(), wName.end());

	char layer01Name[256];
	sprintf(layer01Name, "./MapData/%s_", name.c_str());

	char layer02Name[256];
	sprintf(layer02Name, "%sComponent_Setting.csv", layer01Name);

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
				//�ʵ�����
				if (NULL != token)
				{
					std::vector<TileCell*> rowList = _tileMap[row];
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);

						if (0 <= index)
						{
							TileCell* tilecell = rowList[x];
							Position tileposition;
							tileposition.x = x;
							tileposition.y = row;

							eTileLayer layer;

							layer = (eTileLayer)(index / 1000);

							int activepoint=( index / 100 - layer * 10  );

							eObjectType objectType=(eObjectType)(index % 100);



							SelfMoveObject * move;

							switch (objectType)
							{
							case OBJECT_TYPE_PLAYER:
								move =new Player(L"player");
								move->Init(activepoint, tileposition, layer);
								tilecell->AddTileObject(move);

								_turnList.push_back(move);
								break;
							case OBJECT_TYPE_MONSTER:
								move = new Monster(L"monster");
								move->Init(activepoint, tileposition, layer);
								tilecell->AddTileObject(move);

								_turnList.push_back(move);
								break;
							default:
								break;
							}
							
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


	if (_turnList.size() >= 2)
	{
		_turnCircle = _turnList.begin();
		(*_turnCircle)->InitActivePoint();
	}


}

void Map::Init()
{
	_tileSize = 32;
	int srcX = 0;
	int srcY = 0;


	_height = 16;
	_width = 16;

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


	CreateMap();
	Create_Component();

	

}

void Map::Update(float deltaTime)
{
	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//����� ��ġ�� �������� ���� �ȼ� ��ġ�� ���
	_startX = (-_viewer->GetTileX()*_tileSize) + midX - _tileSize / 2;
	_startY = (-_viewer->GetTileY()*_tileSize) + midY - _tileSize / 2;

	//�ش���ġ�� Ÿ�ϱ׸�
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

	turnUpdate();
}

void Map::turnUpdate()
{
	if (false == (_turnList.size() >= 2))
		return;

	SelfMoveObject * currentTurnOwner = (*_turnCircle);


	if (false == currentTurnOwner->IsActive())
	{

		std::list<SelfMoveObject*>::iterator end = _turnList.end();

		--end;

		if (currentTurnOwner == (*end))
		{
			_turnCircle = _turnList.begin();
		}

		else
			_turnCircle++;


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

	//����
	//�ּ�x=����� ���� Ÿ�� x�� ��ġ-(�߽�����x��ǥ/Ÿ�� ũ��)-1 
	//�ּ�y=����� ���� Ÿ�� y�� ��ġ-(�߽�����y��ǥ/Ÿ�� ũ��)-1
	//�ִ�X=����� ���� Ÿ�� x�� ��ġ+(�߽�����x��ǥ/Ÿ�� ũ��)+1
	//�ִ�y=����� ���� Ÿ�� y�� ��ġ+(�߽�����y��ǥ/Ÿ�� ũ��)+1

	int midX = GameSystem::GetInstance()->GetWidth() / 2;
	int midY = GameSystem::GetInstance()->GetHeight() / 2;

	//����� ��ġ�� �������� ���� �ȼ� ��ġ�� ���
	_startX = (-_viewer->GetTileX()*_tileSize) + midX - _tileSize / 2;
	_startY = (-_viewer->GetTileY()*_tileSize) + midY - _tileSize / 2;

	//�ش���ġ�� Ÿ�ϱ׸�
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