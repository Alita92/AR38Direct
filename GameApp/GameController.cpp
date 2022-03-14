#include "PreCompile.h"
#include "GameController.h"

GameController::GameController() // default constructer 디폴트 생성자
	: CurViewState_(LOCATION::MAX), deltaTime_(0.0f), state_(this), curUsage_(1), curElectricity_(MAX_ELECTRICITIY_RATE), isElecCheckOff_(false)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
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
	// 전력은 (9.6 / 사용량)초마다 1%씩 소모된다 (아무것도 안 할 때 사용량 1)
	// 그 외 2일밤 부터는 고정적으로 추가 전력 소모가 존재
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curUsage_ <= deltaTime_)
	{
		deltaTime_ = 0.0f;
		curElectricity_--;
	}
		// 2일밤 9 %
		// 3일밤 10.8 %
		// 4일밤 13.5 %
		// 5일밤~18 %

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
	// CCTV를 작동시킨 상태입니다.
	// 전력 소모량이 1레벨 상승하며,
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::startNoelec(StateInfo _state)
{
	// 전력이 나간 이후 5초마다 1 / 5 확률로(최대 20초) 노래가 재생되기 시작하고
	// 5초마다 1 / 5 확률로(최대 20초) 노래가 멈추고 화면이 암전된다
	// 이후 2초마다 1 / 5 확률로 프레디가 점프스케어
	isElecCheckOff_ = true;
	deltaTime_ = 0.0f;
	return StateInfo();
}

StateInfo GameController::updateNoelec(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();


	return StateInfo();
}