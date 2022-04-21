#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"
// �з� : 
// �뵵 : 
// ���� : 

class WarningController;
class GameEngineImageRenderer;
class WarningLevel : public GameEngineLevel
{
private:
	friend class WarningController;

public:
	WarningLevel(); // default constructer ����Ʈ ������
	~WarningLevel(); // default destructer ����Ʈ �Ҹ���
	WarningLevel(const WarningLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	WarningLevel(WarningLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	WarningLevel& operator=(const WarningLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	WarningLevel& operator=(const WarningLevel&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

private:
	WarningController* controller_;

};

