#include "PreCompile.h"
#include "GameController.h"

// Enemy AI
#include "AIBonnie.h"

GameController::GameController() // default constructer 디폴트 생성자
	: CurViewState_(LOCATION::OFFICE), CurCCTVState_(LOCATION::SHOWSTAGE), elecUsageTimer_(0.0f), state_(this), curElecUsage_(0), curElectricity_(0.0f), isElecCheckOff_(false)
	, aiBonnie_(nullptr), aiChica_(nullptr), aiFoxy_(nullptr), aiFreddy_(nullptr)
	, curTime_(0), timeUsageTimer_(0.0f), isTimeCheckOff_(false)
	, curDay_(0)
	, lDoorClosed_(false), lDoorLighted_(false), rDoorClosed_(false), rdoorLighted_(false)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}


void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);
	state_.CreateState("NoElec", &GameController::startNoelec, &GameController::updateNoelec);
	state_.CreateState("Win", &GameController::startWin, &GameController::updateWin);

	state_.ChangeState("Idle");
}

void GameController::InitPlayStatus()
{
	CurViewState_ = LOCATION::OFFICE;
	CurCCTVState_ = LOCATION::SHOWSTAGE;
	curElecUsage_ = 1;
	curElectricity_ = MAX_ELECTRICITIY_RATE;
	curTime_ = 0;
	curDay_ = 1;
}

void GameController::InitEnemy()
{
	aiBonnie_ = GetLevel()->CreateActor<AIBonnie>();
//	aiChica_ = GetLevel()->CreateActor<AIChica>();
//	aiFoxy_ = GetLevel()->CreateActor<AIFoxy>();
//	aiFreddy_ = GetLevel()->CreateActor<AIFreddy>();
}

void GameController::InitInput()
{
#ifdef _DEBUG
	// 디버그 전용 인풋
	GameEngineInput::GetInst().CreateKey("Debug_Q", 'Q');
	GameEngineInput::GetInst().CreateKey("Debug_W", 'W');
	GameEngineInput::GetInst().CreateKey("Debug_E", 'E');
	GameEngineInput::GetInst().CreateKey("Debug_A", 'A');
	GameEngineInput::GetInst().CreateKey("Debug_S", 'S');
	GameEngineInput::GetInst().CreateKey("Debug_D", 'D');
#endif


}


void GameController::Start()
{
	InitState();
	InitPlayStatus();
	InitEnemy();
}

void GameController::CheckElectricityUsage()
{
	// 실시간 델타타임을 가산해 전력을 소모시킵니다.
	// 전력이 0이 되면 컨트롤러의 스테이트를 강제로 전환시킵니다.
	if (true == isElecCheckOff_ || curElectricity_ < 0.0f)
	{
		return;
	}
	// 전력은 (9.6 / 사용량)초마다 1%씩 소모된다 (아무것도 안 할 때 사용량 1)
	// 그 외 2일밤 부터는 고정적으로 추가 전력 소모가 존재
	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curElecUsage_ <= elecUsageTimer_)
	{
		elecUsageTimer_ = 0.0f;
		curElectricity_ -= 1.0f;
	}
		// 2일밤 9 %
		// 3일밤 10.8 %
		// 4일밤 13.5 %
		// 5일밤~18 %
	return;
}

void GameController::CheckTime()
{
	// 실시간 델타타임을 가산해 게임 내 시간을 지나게 합니다.
	// 6시로 마커가 도달 시 게임 승리 판정을 내립니다.
	if (true == isTimeCheckOff_ || 6 == curTime_)
	{
		return;
	}

	timeUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (EACH_HOUR_REAL_DURATION <= timeUsageTimer_)
	{
		// 89초가 지나면 시간 마커에 1시간을 더해줍니다.
		timeUsageTimer_ = 0.0f;
		curTime_ += 1;

		if (6 < curTime_)
		{
			GameEngineDebug::MsgBoxError("시간이 7시 이상임에도 게임이 끝나지 않습니다.");
		}

		return;
	}

	return;
}

void GameController::Update(float _Deltatime)
{
	state_.Update();
	CheckTime();
	CheckElectricityUsage();
}

StateInfo GameController::startIdle(StateInfo _state)
{
	CurViewState_ = LOCATION::NONE;

	return StateInfo();
}

StateInfo GameController::updateIdle(StateInfo _state)
{
	if (curTime_ == 6)
	{
		return "Win";
	}

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
	if (curTime_ == 6 || curElectricity_ < 0)
	{
		// 시간, 전기 하나라도 조건 충족 시 강제로 CCTV 모드가 해제됩니다.
		// 이후는 Idle 에서 처리해줍니다.
		return "Idle";
	}

	switch (CurCCTVState_)
	{
		// 현 CCTV가 어디를 지향했는지에 따라
		// 화면을 바꿔 보여줍니다.
	case LOCATION::OFFICE:
		break;
	case LOCATION::LOFFICEDOOR:
		break;
	case LOCATION::ROFFICEDOOR:
		break;
	case LOCATION::SHOWSTAGE:
		break;
	case LOCATION::KITCHEN:
		break;
	case LOCATION::BACKSTAGE:
		break;
	case LOCATION::DININGAREA:
		break;
	case LOCATION::PIRATECOVE:
		break;
	case LOCATION::EASTHALLA:
		break;
	case LOCATION::EASTHALLB:
		break;
	case LOCATION::WESTHALLA:
		break;
	case LOCATION::WESTHALLB:
		break;
	case LOCATION::RESTROOMS:
		break;
	case LOCATION::SUPPLYCLOSET:
		break;
	case LOCATION::NONE:
		break;
	case LOCATION::MAX:
		break;
	default:
		break;
	}

	return StateInfo();
}

StateInfo GameController::startNoelec(StateInfo _state)
{
	isElecCheckOff_ = true;
	isTimeCheckOff_ = true;
	timeUsageTimer_ = 0.0f;
	elecUsageTimer_ = 0.0f;
	return StateInfo();
}

StateInfo GameController::updateNoelec(StateInfo _state)
{

// 5초마다 1 / 5 확률로(최대 20초) 노래가 멈추고 화면이 암전된다
// 이후 2초마다 1 / 5 확률로 프레디가 점프스케어

	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (5.0f <= elecUsageTimer_)
	{	// 전력이 나간 이후 5초마다 1 / 5 확률로(최대 20초) 노래가 재생되기 시작하고
		elecUsageTimer_ = 0.0f;

		
	}

	return StateInfo();
}

StateInfo GameController::startWin(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateWin(StateInfo _state)
{
	return StateInfo();
}