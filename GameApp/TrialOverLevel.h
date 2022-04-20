#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

class TrialOverLevel : public GameEngineLevel
{
private:
	 friend class TrialOverController;

public:
	TrialOverLevel(); // default constructer ����Ʈ ������
	~TrialOverLevel(); // default destructer ����Ʈ �Ҹ���
	TrialOverLevel(const TrialOverLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	TrialOverLevel(TrialOverLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	TrialOverLevel& operator=(const TrialOverLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TrialOverLevel& operator=(const TrialOverLevel&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	TrialOverController* controller_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

