#include "State.h"

#include "Sprite.h"

#include "SelfMoveObject.h"
State::State()
{
}

State::~State()
{

}
void State::Init(SelfMoveObject * moveObject)
{
	_moveObject = moveObject;

	WCHAR textureFileName[256];

	wsprintf(textureFileName, L"./Sprite/%s/Sprite.png", _moveObject->GetName().c_str());

	//left
	{
		Sprite * sprite = new Sprite(textureFileName, L"./Sprite/player/left.json");
		sprite->Init();
		_spriteList[eDirection::DIRCTION_LEFT] = sprite;
	}
	//Right
	{
		Sprite * sprite = new Sprite(textureFileName, L"./Sprite/player/Right.json");
		sprite->Init();
		_spriteList[eDirection::DIRCTION_RIGHT] = sprite;
	}
	//Up
	{
		Sprite * sprite = new Sprite(textureFileName, L"./Sprite/player/Up.json");
		sprite->Init();
		_spriteList[eDirection::DIRCTION_UP] = sprite;
	}
	//Down
	{
		Sprite * sprite = new Sprite(textureFileName, L"./Sprite/player/Down.json");
		sprite->Init();
		_spriteList[eDirection::DIRCTION_DOWN] = sprite;
	}

}
void State::Start()
{
	_nextState = eState::STATE_NONE;
}
void State::Stop()
{

}
void State::Update(float deltaTime)
{

	_spriteList[_moveObject->GetDirection()]->Update(deltaTime);

	if (eState::STATE_NONE != _nextState)
	{
		_moveObject->changeState(_nextState);
		return;
	}
}
void State::render()
{
	_spriteList[_moveObject->GetDirection()]->setPostition(_moveObject->GetPositionX(),_moveObject->GetPositionY());
	_spriteList[_moveObject->GetDirection()]->render();
}
void State::DeInit()
{
	for (std::map<eDirection, Sprite*>::iterator itr = _spriteList.begin(); itr != _spriteList.end(); itr++)
	{
		_spriteList[_moveObject->GetDirection()]->deInit();
	}
}

void State::NextState(eState stateType)
{
	_nextState = stateType;
}