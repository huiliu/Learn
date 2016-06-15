#pragma once
class iSkill
{
public:
	iSkill();
	virtual ~iSkill();

	virtual void Launch() = 0;						// 开始施放技能
	virtual bool HaveLaunch() const = 0;			// 判断技能是否开始施放
	virtual void DoEffect() = 0;					// 产生技能效果
	virtual bool IsInCoolInterval() const = 0;		// 技能是否处于冷却中
	virtual void DoCool() = 0;						// 执行技能冷却
};

