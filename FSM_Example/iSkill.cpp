#include "iSkill.h"



iSkill::iSkill()
{
}


iSkill::~iSkill()
{
}


class FireBallSkill
{
public:
	FireBallSkill();
	~FireBallSkill();

	virtual void Launch();
	virtual bool HaveLaunch() const { return m_bLaunched; }			// 判断技能是否开始施放
	virtual void DoEffect();					// 产生技能效果
	virtual bool IsInCoolInterval() { return m_bInCooled; }			// 技能是否处于冷却中
	virtual void DoCool();						// 执行技能冷却

private:
	bool m_bLaunched;
	bool m_bInCooled;
};

FireBallSkill::FireBallSkill()
	: m_bLaunched(false)
	, m_bInCooled(false)
{
}

FireBallSkill::~FireBallSkill()
{
}

void FireBallSkill::Launch()
{

}


void FireBallSkill::DoEffect()
{

}

void FireBallSkill::DoCool()
{

}