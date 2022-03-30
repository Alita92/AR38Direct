#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class IntermissionController;
class GameEngineImageRenderer;
class IntermissionScreen : public GameEngineActor
{
private:
	friend IntermissionController;

public:
	IntermissionScreen(); // default constructer ����Ʈ ������
	~IntermissionScreen(); // default destructer ����Ʈ �Ҹ���
	IntermissionScreen(const IntermissionScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	IntermissionScreen(IntermissionScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	IntermissionScreen& operator=(const IntermissionScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	IntermissionScreen& operator=(const IntermissionScreen&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* mainRenderer_;
	// ��ũ�� ��ü�� �����ϴ� ����

	GameEngineImageRenderer* typoRenderer_;
	// DAY Ÿ������ �����մϴ�.

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

