#pragma once
class iSkill
{
public:
	iSkill();
	virtual ~iSkill();

	virtual void Launch() = 0;						// ��ʼʩ�ż���
	virtual bool HaveLaunch() const = 0;			// �жϼ����Ƿ�ʼʩ��
	virtual void DoEffect() = 0;					// ��������Ч��
	virtual bool IsInCoolInterval() const = 0;		// �����Ƿ�����ȴ��
	virtual void DoCool() = 0;						// ִ�м�����ȴ
};

