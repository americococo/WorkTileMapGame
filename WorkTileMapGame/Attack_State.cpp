#include "Attack_State.h"

#include "GameSystem.h"

#include "SelfMoveObject.h"
#include "MessageFrom.h"
#include "MessagePost.h"


#include "GameScene.h"
#include "SceneManager.h"
#include "Map.h"
Attack_State::Attack_State()
{
}


Attack_State::~Attack_State()
{
}
void Attack_State::Start()
{
	State::Start();


	Component * com = _moveObject->GetTarget();

	MessageFrom from;
	from.sender = _moveObject;
	from.reciver = (SelfMoveObject*)com;

	from.message = L"Attack";

	((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->AddMessage(from);

	_moveObject->DecressActivePoint(_moveObject->GetMaxActivePoint());

	_moveObject->ResetTarget();
}
void Attack_State::Stop()
{
	State::Stop();
}
void Attack_State::Update(float deltaTime)
{
	State::Update(deltaTime);

	_nextState = eState::STATE_IDLE;
}
void Attack_State::render()
{
	State::render();
}
void Attack_State::DeInit()
{
	State::DeInit();
}