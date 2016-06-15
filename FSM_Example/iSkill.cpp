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
	virtual bool HaveLaunch() const { return m_bLaunched; }			// �жϼ����Ƿ�ʼʩ��
	virtual void DoEffect();					// ��������Ч��
	virtual bool IsInCoolInterval() { return m_bInCooled; }			// �����Ƿ�����ȴ��
	virtual void DoCool();						// ִ�м�����ȴ

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