#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 게임의 진행과 플레이어의 상황을 비시각적으로 제어하는 역할의 클래스입니다.
// 시각적인 용도를 결정하는 클래스(CCTV 스크린 등) 은 이 게임컨트롤러의 피드백을 받아 움직이게 합니다.

class GameEngineImageRenderer;
class AIBonnie;
class AIChica;
class AIFoxy;
class AIFreddy;
class GameController : public GameEngineActor
{
public:
	GameController(); // default constructer 디폴트 생성자
	~GameController(); // default destructer 디폴트 소멸자
	GameController(const GameController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameController(GameController&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameController& operator=(const GameController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameController& operator=(const GameController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitState();



private:
	// 컨트롤러 척도
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f;
	const int START_TIME_MARKER = 0;
	const int END_TIME_MARKER = 6;
	const float EACH_HOUR_REAL_DURATION = 89.0f;
	const int FIRST_DAY = 1;
	const int MAX_DAY = 5;

	// 스테이지 변수
	int curDay_;

	// 전기 변수
	float curElectricity_;
	int curElecUsage_;
	float elecUsageTimer_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();

	// 게임 시간 변수
	bool isTimeCheckOff_;
	int curTime_;
	float timeUsageTimer_;
	void CheckTime();


	// 문 변수
	bool isLdoorClosed_;
	bool isRdoorClosed_;
	bool lDoorLighted_;
	bool rdoorLighted_;


	// 전기 고갈시 사용 변수


	// 전기, 게임 시간 초기화
	void InitPlayStatus();

	// 렌더러들 디폴트 Position

	float4 DEFAULT_FAN_POS_OFFICE = { 49.0f, -41.0f, -1.0f };
	float4 DEFAULT_FAN_POS_CCTV = { 49.0f, -41.0f, 1.0f };
	float4 DEFAULT_CCTV_POS_CCTV = { 0.0f,0.0f,-2.0f };

protected:
	void InitAnimation();


	GameEngineImageRenderer* mainRenderer_;
	GameEngineImageRenderer* CCTVRenderer_;
	GameEngineImageRenderer* fanRenderer_;
	GameEngineImageRenderer* lDoorRenderer_;
	GameEngineImageRenderer* rDoorRenderer_;

	
private:
	// 애니매트로닉스 인공지능 슬롯
	AIBonnie* aiBonnie_;
	AIChica* aiChica_;
	AIFoxy* aiFoxy_;
	AIFreddy* aiFreddy_;

	// 인공지능 초기화
	void InitEnemy();

private:
	LOCATION CurViewState_;
	LOCATION CurCCTVState_;

private: // FSM 은 기성 시스템을 가져왔으나 선생님이 새로 만드실 경우 리팩토링을 염두에 둡니다.
	GameEngineFSM<GameController> state_;

#pragma region States
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startCCTVOpen(StateInfo _state);
	StateInfo updateCCTVOpen(StateInfo _state);

	StateInfo startCCTV(StateInfo _state);
	StateInfo updateCCTV(StateInfo _state);

	StateInfo startCCTVClose(StateInfo _state);
	StateInfo updateCCTVClose(StateInfo _state);

	StateInfo startNoelec(StateInfo _state);
	StateInfo updateNoelec(StateInfo _state);

	StateInfo startWin(StateInfo _state);
	StateInfo updateWin(StateInfo _state);


};

