#include "PreCompile.h"
#include "GameController.h"

GameController::GameController() // default constructer ����Ʈ ������
	: CurViewState_(LOCATION::MAX), deltaTime_(0.0f), state_(this), curUsage_(1), curElectricity_(MAX_ELECTRICITIY_RATE), isElecCheckOff_(false)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}


void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);
	state_.CreateState("NoElec", &GameController::startNoelec, &GameController::updateNoelec);
	state_.ChangeState("Idle");
}

void GameController::Start()
{
	InitState();
}

void GameController::Update(float _Deltatime)
{
	state_.Update();
	CheckElectricityUsage();
}

void GameController::CheckElectricityUsage()
{
	if (true == isElecCheckOff_)
	{
		return;
	}
	// ������ (9.6 / ��뷮)�ʸ��� 1%�� �Ҹ�ȴ� (�ƹ��͵� �� �� �� ��뷮 1)
	// �� �� 2�Ϲ� ���ʹ� ���������� �߰� ���� �Ҹ� ����
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curUsage_ <= deltaTime_)
	{
		deltaTime_ = 0.0f;
		curElectricity_--;
	}
		// 2�Ϲ� 9 %
		// 3�Ϲ� 10.8 %
		// 4�Ϲ� 13.5 %
		// 5�Ϲ�~18 %

}

StateInfo GameController::startIdle(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateIdle(StateInfo _state)
{

	if (curElectricity_ < 0)
	{
		return "Noelec";
	}

	return StateInfo();
}

StateInfo GameController::startCCTV(StateInfo _state)
{
	// CCTV�� �۵���Ų �����Դϴ�.
	// ���� �Ҹ��� 1���� ����ϸ�,
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::startNoelec(StateInfo _state)
{
	// ������ ���� ���� 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ����Ǳ� �����ϰ�
	// 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ���߰� ȭ���� �����ȴ�
	// ���� 2�ʸ��� 1 / 5 Ȯ���� ������ �������ɾ�
	isElecCheckOff_ = true;
	deltaTime_ = 0.0f;
	return StateInfo();
}

StateInfo GameController::updateNoelec(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();


	return StateInfo();
}