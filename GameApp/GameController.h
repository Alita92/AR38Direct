#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 게임의 진행과 플레이어의 상황을 비시각적으로 제어하는 역할의 클래스입니다.
// 시각적인 용도를 결정하는 클래스(CCTV 스크린 등) 은 이 게임컨트롤러의 피드백을 받아 움직이게 합니다.

class GameController : public GameEngineActor
{
public:
	GameController(); // default constructer 디폴트 생성자
	~GameController(); // default destructer 디폴트 소멸자
	GameController(const GameController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameController(GameController&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameController& operator=(const GameController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameController& operator=(const GameController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitState();

private: // FSM 은 기성 시스템을 가져왔으나 선생님이 새로 만드실 경우 리팩토링을 염두에 둡니다.

	GameEngineFSM<GameController> state_;

#pragma region States
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);
	
	StateInfo startCCTV(StateInfo _state);
	StateInfo updateCCTV(StateInfo _state);

	// 배터리가 0.0 이하로 떨어 질 시 강제 전환되는 State 입니다.
	StateInfo startNoelec(StateInfo _state);
	StateInfo updateNoelec(StateInfo _state);

private:
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f;
	float curElectricity_;
	int curUsage_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();



private:
	LOCATION CurViewState_;

	float deltaTime_;
	

};

