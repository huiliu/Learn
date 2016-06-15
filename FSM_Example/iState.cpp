#include "iState.h"
#include "iSkill.h"

class SkillLaunch : public iState
{
public:
	SkillLaunch();
	~SkillLaunch();

	virtual void Execute(iSkill* pSkill);
	virtual void OnEnterState(iSkill* pSkill);
	virtual void OnExitState(iSkill* pSkill);

private:

};

SkillLaunch::SkillLaunch()
{
}

SkillLaunch::~SkillLaunch()
{
}

void SkillLaunch::Execute(iSkill* pSkill)
{
	if (!pSkill->HaveLaunch())
	{
		pSkill->Launch();
	}
}

void SkillLaunch::OnEnterState(iSkill* pSkill)
{

}

void SkillLaunch::OnExitState(iSkill* pSkill)
{

}

class SkillDoEffect : public iState
{
public:
	SkillDoEffect();
	~SkillDoEffect();

	virtual void Execute(iSkill* pSkill);
	virtual void OnEnterState(iSkill* pSkill);
	virtual void OnExitState(iSkill* pSkill);

private:

};

SkillDoEffect::SkillDoEffect()
{
}

SkillDoEffect::~SkillDoEffect()
{
}


void SkillDoEffect::Execute(iSkill* pSkill)
{
	pSkill->DoEffect();
}

void SkillDoEffect::OnEnterState(iSkill* pSkill)
{

}

void SkillDoEffect::OnExitState(iSkill* pSkill)
{

}