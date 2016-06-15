#pragma once

class iSkill;

class iState
{
public:
	virtual ~iState() {}

	virtual void OnEnterState(iSkill* pSkill) = 0;
	virtual void OnExitState(iSkill* pSkill) = 0;
	virtual void Execute(iSkill* pSkill) = 0;
};

