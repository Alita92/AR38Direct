#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ENUM.h"


// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class IntermissionScreen : public GameEngineActor
{
public:
	IntermissionScreen(); // default constructer ����Ʈ ������
	~IntermissionScreen(); // default destructer ����Ʈ �Ҹ���
	IntermissionScreen(const IntermissionScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	IntermissionScreen(IntermissionScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	IntermissionScreen& operator=(const IntermissionScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	IntermissionScreen& operator=(const IntermissionScreen&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* mainRenderer_;
	// ��ũ�� ��ü�� �����մϴ�. ���� ���������� �����ϳ� ù ���� ���� ���� �Ź� ��������Ʈ�� �������� �����Դϴ�.

	GameEngineImageRenderer* typoRenderer_;
	// DAY Ÿ������ �����մϴ�.

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	DAY curDay_;

public:
	void PromoteIntermissionTo(DAY _day);
};

