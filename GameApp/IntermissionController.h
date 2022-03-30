#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
// 설명 : 

class GlitchScreen;
class FadeScreen;
class IntermissionScreen;
class IntermissionController : public GameEngineActor
{
private:
	friend IntermissionScreen;

public:
	IntermissionController(); // default constructer 디폴트 생성자
	~IntermissionController(); // default destructer 디폴트 소멸자
	IntermissionController(const IntermissionController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	IntermissionController(IntermissionController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	IntermissionController& operator=(const IntermissionController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	IntermissionController& operator=(const IntermissionController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	static DAY curDay_;

protected:
	IntermissionScreen* intermissionScreen_;
	FadeScreen* fadeScreen_;
	GlitchScreen* glitchScreen_;
	
private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void StateInit();
	void SwitchDayRenderer();

private:
	float deltaTime_;

private: // FSM 은 기성 시스템을 가져왔으나 선생님이 새로 만드실 경우 리팩토링을 염두에 둡니다.
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

