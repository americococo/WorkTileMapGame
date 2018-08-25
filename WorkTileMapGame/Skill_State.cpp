#include "Skill_State.h"
#include "SelfMoveObject.h"
void Skill_State::Start()
{
	State::Start();
	_skillType = _moveObject->GetSkillType();

	_moveObject->StartSkill();
}
void Skill_State::Stop()
{
	State::Stop();
	_moveObject->DecressActivePoint(_moveObject->GetMaxActivePoint());
	_moveObject->SetSkillType(SkillType::SKILLTYPE_NONE);
}
void Skill_State::Update(float deltaTime)
{
	_moveObject->UpdateSkill(deltaTime);

	State::Update(deltaTime);
}
void Skill_State::render()
{
	State::render();
}
void Skill_State::DeInit()
{
	State::DeInit();
}
