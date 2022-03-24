#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : Ÿ��Ʋ -> �÷��� | �÷��� ���� �� �̵� �� ��� �̵��ϴ� �����Դϴ�.


class IntermissionLevel : public GameEngineLevel
{
public:
	IntermissionLevel(); // default constructer ����Ʈ ������
	~IntermissionLevel(); // default destructer ����Ʈ �Ҹ���
	IntermissionLevel(const IntermissionLevel& _other) = delete; // default Copy constructer ����Ʈ ���������
	IntermissionLevel(IntermissionLevel&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	IntermissionLevel& operator=(const IntermissionLevel& _other) = delete; // default Copy operator ����Ʈ ���� ������
	IntermissionLevel& operator=(const IntermissionLevel&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	DAY curDay_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

