#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 게임의 진행과 플레이어의 상황을 비시각적으로 제어하는 역할의 클래스입니다.
// 시각적인 용도를 결정하는 클래스(CCTV 스크린 등) 은 이 게임컨트롤러의 피드백을 받아 움직이게 합니다.

class GameEngineImageRenderer;
class GlitchScreen;
class FadeScreen;
class AIBonnie;
class AIChica;
class AIFoxy;
class AIFreddy;
class UIController;
class GameController : public GameEngineActor
{
private:
	friend UIController;
	friend AIBonnie;
	friend AIChica;
	friend AIFoxy;
	friend AIFreddy;

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
	void InitUIController();
	void InitState();
	void InitAnimation();
	void InitPlayStatus();
	void InitEnemy();
	void InitScreenEffects();

private:
	void CheckOfficeInput();

private:
	UIController* UIController_;
	FadeScreen* fadeScreen_;
	GlitchScreen* glitchScreen_;

	// 컨트롤러 척도
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f /*9.6f*/ ;
	const int START_TIME_MARKER = 0;
	const int END_TIME_MARKER = 6;
	const float EACH_HOUR_REAL_DURATION = 89.0f /*89.0f*/;
	const int FIRST_DAY = 1;
	const int MAX_DAY = 5;
	const float MAXIMUM_PLAYDEAD_DURATION = 20.0f;

	// 스테이지 변수
	int curDay_;

	// 전기 변수
	float curPowerRate_;
	int curPowerLevel_;
	float elecUsageTimer_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();

	// 게임 시간 변수
	bool isTimeCheckOff_;
	int curTime_;
	float timeUsageTimer_;
	void CheckTime();

	float playDeadTimer_;
	float deathSceneTimer_;

	// 폭시 전용 델타타임
	float foxyDeathTimer_;
	bool isPirateCoveChecked_;
	bool isFoxyRunning_;

	// 문 변수
	bool isLdoorClosed_;
	bool isRdoorClosed_;
	bool isLdoorLighted_;
	bool isRdoorLighted_;

	// 전기 고갈시 사용 변수
	float noElecDeltaTime_;
	GameEngineRandom randomGenerator_;
	int noElecTimerCounter_;

	// 애니매트로닉스 포착 변수
	int bonnieDice_;
	int chicaDice_;

	// 심령 효과 변수
	bool isAnomalyOn_;
	int anomalyDice_;

protected:
	void CollisionCCTVButton(GameEngineCollision* _other);
	void CollisionMuteCall(GameEngineCollision* _other);
	
	void CollisionCam1A(GameEngineCollision* _other);
	void CollisionCam1B(GameEngineCollision* _other);
	void CollisionCam1C(GameEngineCollision* _other);
	void CollisionCam5(GameEngineCollision* _other);
	void CollisionCam3(GameEngineCollision* _other);
	void CollisionCam2A(GameEngineCollision* _other);
	void CollisionCam2B(GameEngineCollision* _other);
	void CollisionCam7(GameEngineCollision* _other);
	void CollisionCam6(GameEngineCollision* _other);
	void CollisionCam4A(GameEngineCollision* _other);
	void CollisionCam4B(GameEngineCollision* _other);

public:
	// 렌더러들 디폴트 Position

	float4 DEFAULT_FAN_POS_OFFICE = { 49.0f, -41.0f, -1.0f };
	float4 DEFAULT_FAN_POS_CCTV = { 49.0f, -41.0f, 1.0f };
	float4 DEFAULT_CCTV_POS_CCTV = { 0.0f,0.0f,-2.0f };

protected:
	GameEngineImageRenderer* mainRenderer_;
	GameEngineImageRenderer* CCTVAnimationRenderer_;
	GameEngineImageRenderer* CCTVRealRenderer_;

	GameEngineImageRenderer* fanRenderer_;
	GameEngineImageRenderer* lDoorRenderer_;
	GameEngineImageRenderer* rDoorRenderer_;

	// 주의!!! 하단 렌더러는 폭시 복도 애니메이션 전용!!!
	GameEngineImageRenderer* foxyRunningRenderer_;


private:
	PLAYERSTATUS CurPlayerState_;
	LOCATION CurCCTVState_;
	LOCATION PrevCCTVState_;

private:
	// 애니매트로닉스 인공지능 슬롯
	AIBonnie* aiBonnie_;
	AIChica* aiChica_;
	AIFoxy* aiFoxy_;
	AIFreddy* aiFreddy_;


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

	StateInfo startNoElec(StateInfo _state);
	StateInfo updateNoElec(StateInfo _state);

	StateInfo startHeisComing(StateInfo _state);
	StateInfo updateHeisComing(StateInfo _state);

	StateInfo startHeKillsYou(StateInfo _state);
	StateInfo updateHeKillsYou(StateInfo _state);

	StateInfo startBonnieDeath(StateInfo _state);
	StateInfo updateBonnieDeath(StateInfo _state);

	StateInfo startChicaDeath(StateInfo _state);
	StateInfo updateChicaDeath(StateInfo _state);

	StateInfo startFoxyDeath(StateInfo _state);
	StateInfo updateFoxyDeath(StateInfo _state);

	StateInfo startFreddyDeath(StateInfo _state);
	StateInfo updateFreddyDeath(StateInfo _state);

	StateInfo startNoElecDeath(StateInfo _state);
	StateInfo updateNoElecDeath(StateInfo _state);

	StateInfo startWin(StateInfo _state);
	StateInfo updateWin(StateInfo _state);
#pragma endregion States

};

