#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : ������ ����� �÷��̾��� ��Ȳ�� ��ð������� �����ϴ� ������ Ŭ�����Դϴ�.
// �ð����� �뵵�� �����ϴ� Ŭ����(CCTV ��ũ�� ��) �� �� ������Ʈ�ѷ��� �ǵ���� �޾� �����̰� �մϴ�.

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

protected:

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitState();

private: // FSM �� �⼺ �ý����� ���������� �������� ���� ����� ��� �����丵�� ���ο� �Ӵϴ�.

	GameEngineFSM<GameController> state_;

#pragma region States
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);
	
	StateInfo startCCTV(StateInfo _state);
	StateInfo updateCCTV(StateInfo _state);

	// ���͸��� 0.0 ���Ϸ� ���� �� �� ���� ��ȯ�Ǵ� State �Դϴ�.
	StateInfo startNoelec(StateInfo _state);
	StateInfo updateNoelec(StateInfo _state);

private:
	const float MAX_ELECTRICITIY_RATE = 100.0f;
	const float ELECTRICITY_DEFAULT_USAGE = 9.6f;
	const int START_TIME_MARKER = 0;
	const int END_TIME_MARKER = 6;
	const float EACH_HOUR_REAL_DURATION = 89.0f;

	int curTime_;
	float curElectricity_;
	int curUsage_;
	bool isElecCheckOff_;
	void CheckElectricityUsage();
	void InitPlayStatus();


private:
	// �ִϸ�Ʈ�δн� �ΰ����� ����
	AIBonnie* aiBonnie_;
	AIChica* aiChica_;
	AIFoxy* aiFoxy_;
	AIFreddy* aiFreddy_;

	void InitEnemy();

private:
	LOCATION CurViewState_;
	float deltaTime_;
};

