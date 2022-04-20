#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
// 설명 : 

class IntermissionLevel;
class GlitchScreen;
class FadeScreen;
class GameEngineCollision;
class IntermissionScreen;
class IntermissionController : public GameEngineActor
{
private:
	friend IntermissionLevel;
	friend IntermissionScreen;

public:
	IntermissionController(); // default constructer 디폴트 생성자
	~IntermissionController(); // default destructer 디폴트 소멸자
	IntermissionController(const IntermissionController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	IntermissionController(IntermissionController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	IntermissionController& operator=(const IntermissionController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	IntermissionController& operator=(const IntermissionController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자


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

	void ControllerReloading();

private:
	// SOUND PLAYER
	GameEngineSoundPlayer awakePlayer_;

private:
	float deltaTime_;

private: 
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

