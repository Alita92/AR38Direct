#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : ������ ����� �÷��̾��� ��Ȳ�� ��ð������� �����ϴ� ������ Ŭ�����Դϴ�.
// �ð����� �뵵�� �����ϴ� Ŭ����(CCTV ��ũ�� ��) �� �� ������Ʈ�ѷ��� �ǵ���� �޾� �����̰� �մϴ�.

class GameEngineImageRenderer;
class AIBonnie;
class AIChica;
class AIFoxy;
class AIFreddy;
class GameController : public GameEngineActor
{
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
	void InitState();



private:
	// ��Ʈ�ѷ� ô��
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f;
	const int START_TIME_MARKER = 0;
	const int END_TIME_MARKER = 6;
	const float EACH_HOUR_REAL_DURATION = 89.0f;
	const int FIRST_DAY = 1;
	const int MAX_DAY = 5;

	// �������� ����
	int curDay_;

	// ���� ����
	float curElectricity_;
	int curElecUsage_;
	float elecUsageTimer_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();

	// ���� �ð� ����
	bool isTimeCheckOff_;
	int curTime_;
	float timeUsageTimer_;
	void CheckTime();


	// �� ����
	bool isLdoorClosed_;
	bool isRdoorClosed_;
	bool lDoorLighted_;
	bool rdoorLighted_;


	// ���� ���� ��� ����


	// ����, ���� �ð� �ʱ�ȭ
	void InitPlayStatus();

	// �������� ����Ʈ Position

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
	// �ִϸ�Ʈ�δн� �ΰ����� ����
	AIBonnie* aiBonnie_;
	AIChica* aiChica_;
	AIFoxy* aiFoxy_;
	AIFreddy* aiFreddy_;

	// �ΰ����� �ʱ�ȭ
	void InitEnemy();

private:
	LOCATION CurViewState_;
	LOCATION CurCCTVState_;

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

	StateInfo startNoelec(StateInfo _state);
	StateInfo updateNoelec(StateInfo _state);

	StateInfo startWin(StateInfo _state);
	StateInfo updateWin(StateInfo _state);


};

