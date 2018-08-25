#pragma once
#include "State.h"
enum SkillType
{
	SKILLTYPE_RANGEATTACK,
	SKILLTYPE_SERCH,
	SKILLTYPE_HEALING,
	SKILLTYPE_NONE,
};

class Skill_State:public State
{
	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();



	SkillType _skillType;
};