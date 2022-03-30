#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"
// �з� : 
// �뵵 : 
// ���� : 

class FadeScreen;
class IntermissionScreen;
class IntermissionController : public GameEngineActor
{
private:
	friend IntermissionScreen;

public:
	IntermissionController(); // default constructer ����Ʈ ������
	~IntermissionController(); // default destructer ����Ʈ �Ҹ���
	IntermissionController(const IntermissionController& _other) = delete; // default Copy constructer ����Ʈ ���������
	IntermissionController(IntermissionController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	IntermissionController& operator=(const IntermissionController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	IntermissionController& operator=(const IntermissionController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	static DAY curDay_;

protected:
	IntermissionScreen* intermissionScreen_;
	FadeScreen* fadeScreen_;
	
private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void StateInit();
	void SwitchDayRenderer();

private:
	float deltaTime_;

private: // FSM �� �⼺ �ý����� ���������� �������� ���� ����� ��� �����丵�� ���ο� �Ӵϴ�.
	GameEngineFSM<IntermissionController> state_;

#pragma region States
	StateInfo startStandby(StateInfo _state);
	StateInfo updateStandby(StateInfo _state);

	StateInfo startProceed(StateInfo _state);
	StateInfo updateProceed(StateInfo _state);

	StateInfo startFadeOut(StateInfo _state);
	StateInfo updateFadeOut(StateInfo _state);

#pragma endregion States
};

