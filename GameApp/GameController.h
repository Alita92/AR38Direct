#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : ������ ����� �÷��̾��� ��Ȳ�� ��ð������� �����ϴ� ������ Ŭ�����Դϴ�.
// �ð����� �뵵�� �����ϴ� Ŭ����(CCTV ��ũ�� ��) �� �� ������Ʈ�ѷ��� �ǵ���� �޾� �����̰� �մϴ�.

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
	GameController(); // default constructer ����Ʈ ������
	~GameController(); // default destructer ����Ʈ �Ҹ���
	GameController(const GameController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameController(GameController&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������
	GameController& operator=(const GameController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameController& operator=(const GameController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

	// ��Ʈ�ѷ� ô��
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f /*9.6f*/ ;
	const int START_TIME_MARKER = 0;
	const int END_TIME_MARKER = 6;
	const float EACH_HOUR_REAL_DURATION = 89.0f /*89.0f*/;
	const int FIRST_DAY = 1;
	const int MAX_DAY = 5;
	const float MAXIMUM_PLAYDEAD_DURATION = 20.0f;

	// �������� ����
	int curDay_;

	// ���� ����
	float curPowerRate_;
	int curPowerLevel_;
	float elecUsageTimer_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();

	// ���� �ð� ����
	bool isTimeCheckOff_;
	int curTime_;
	float timeUsageTimer_;
	void CheckTime();

	float playDeadTimer_;
	float deathSceneTimer_;

	// ���� ���� ��ŸŸ��
	float foxyDeathTimer_;
	bool isPirateCoveChecked_;
	bool isFoxyRunning_;

	// �� ����
	bool isLdoorClosed_;
	bool isRdoorClosed_;
	bool isLdoorLighted_;
	bool isRdoorLighted_;

	// ���� ���� ��� ����
	float noElecDeltaTime_;
	GameEngineRandom randomGenerator_;
	int noElecTimerCounter_;

	// �ִϸ�Ʈ�δн� ���� ����
	int bonnieDice_;
	int chicaDice_;

	// �ɷ� ȿ�� ����
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
	// �������� ����Ʈ Position

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

	// ����!!! �ϴ� �������� ���� ���� �ִϸ��̼� ����!!!
	GameEngineImageRenderer* foxyRunningRenderer_;


private:
	PLAYERSTATUS CurPlayerState_;
	LOCATION CurCCTVState_;
	LOCATION PrevCCTVState_;

private:
	// �ִϸ�Ʈ�δн� �ΰ����� ����
	AIBonnie* aiBonnie_;
	AIChica* aiChica_;
	AIFoxy* aiFoxy_;
	AIFreddy* aiFreddy_;


private: // FSM �� �⼺ �ý����� ���������� �������� ���� ����� ��� �����丵�� ���ο� �Ӵϴ�.
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

