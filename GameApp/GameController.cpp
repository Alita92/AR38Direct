#include "PreCompile.h"
#include "GameController.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// UIController
#include "UIController.h"

// Enemy AI
#include "AIBonnie.h"

GameController::GameController() // default constructer 디폴트 생성자
	: CurViewState_(LOCATION::OFFICE), CurCCTVState_(LOCATION::SHOWSTAGE), elecUsageTimer_(0.0f), state_(this), curPowerLevel_(0), curPowerRate_(0.0f), isElecCheckOff_(false)
	, aiBonnie_(nullptr), aiChica_(nullptr), aiFoxy_(nullptr), aiFreddy_(nullptr)
	, curTime_(0), timeUsageTimer_(0.0f), isTimeCheckOff_(false)
	, curDay_(0)
	, isLdoorClosed_(false), lDoorLighted_(false), isRdoorClosed_(false), rdoorLighted_(false)
	, noElecDeltaTime_(0.0f), noElecTimerCounter_(0)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::InitUIController()
{
	UIController_ = GetLevel()->CreateActor<UIController>();
}

void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);

	state_.CreateState("CCTVOpen", &GameController::startCCTVOpen, &GameController::updateCCTVOpen);
	state_.CreateState("CCTVClose", &GameController::startCCTVClose, &GameController::updateCCTVClose);

	state_.CreateState("CCTV", &GameController::startCCTV, &GameController::updateCCTV);
	
	state_.CreateState("NoElec", &GameController::startNoElec, &GameController::updateNoElec);
	state_.CreateState("HeisComing", &GameController::startHeisComing, &GameController::updateHeisComing);
	state_.CreateState("HeKillsYou", &GameController::startHeKillsYou, &GameController::updateHeKillsYou);
	state_.CreateState("NoElecDeath", &GameController::startNoElecDeath, &GameController::updateNoElecDeath);

	state_.CreateState("Win", &GameController::startWin, &GameController::updateWin);

	state_.ChangeState("Idle");
}

void GameController::InitPlayStatus()
{
	CurViewState_ = LOCATION::OFFICE;
	CurCCTVState_ = LOCATION::SHOWSTAGE;
	curPowerLevel_ = 1;
	curPowerRate_ = MAX_ELECTRICITIY_RATE;
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

void GameController::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::BACKGROUND0)});
		mainRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
		mainRenderer_->CreateAnimationFolder("NoElec", "NoElec", 0.04f, true);
		mainRenderer_->CreateAnimationFolder("NoElecBlink", "NoElecBlink", 0.04f, false);
		mainRenderer_->CreateAnimationFolder("NoElecFreddy", "NoElecFreddy", 0.04f, false);
	}

	{
		fanRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		fanRenderer_->SetImage("OfficeFanDefault.png", true);
		fanRenderer_->GetTransform()->SetLocalPosition({ 49.0f, -41.0f, static_cast<float>(RenderOrder::OBJECT1) });
		fanRenderer_->CreateAnimation("OfficeFan.png", "OfficeFan", 0, 2, 0.02f);
		fanRenderer_->SetChangeAnimation("OfficeFan");
	}

	{
		lDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		lDoorRenderer_->SetImage("LdoorStatic.png", true);
		lDoorRenderer_->GetTransform()->SetLocalPosition({ -550.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1)});
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorClose", 14, 0, 0.04f, false);
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorOpen", 0, 14, 0.04f, false);
	}

	{
		rDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 550.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1) });
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorClose", 14, 0, 0.04f, false);
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorOpen", 0, 14, 0.04f, false);
	}

	{		
		CCTVRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVRenderer_->SetImage("ShowStage_Default.png", true);
		CCTVRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT0) });
		CCTVRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVOpen", 0, 9, 0.04f, false);
		CCTVRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVClose", 9, 0, 0.04f, false);
		CCTVRenderer_->Off();
	}
}

void GameController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f ,0.0f, 10.0f });
	InitUIController();
	InitState();
	InitAnimation();
	InitPlayStatus();
	InitEnemy();

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P');
	}
	
}



void GameController::CheckTime()
{
	// 실시간 델타타임을 가산해 게임 내 시간을 지나게 합니다.
	// 6시로 마커가 도달 시 게임 승리 판정을 내립니다.
	if (6 == curTime_)
	{
		return;
	}

	timeUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (EACH_HOUR_REAL_DURATION <= timeUsageTimer_)
	{
		// 89초가 지나면 시간 마커에 1시간을 더해줍니다.
		timeUsageTimer_ = 0.0f;
		curTime_ += 1;
		UIController_->SetTimeRenderer(curTime_);

		if (6 < curTime_)
		{
			GameEngineDebug::MsgBoxError("시간이 7시 이상임에도 게임이 끝나지 않습니다.");
		}

		return;
	}

	return;
}

void GameController::CheckElectricityUsage()
{
	// 실시간 델타타임을 가산해 전력을 소모시킵니다.
	// 전력이 0이 되면 컨트롤러의 스테이트를 강제로 전환시킵니다.


	if (true == isElecCheckOff_ || curPowerRate_ <= 0.0f)
	{
		return;
	}
	// 전력은 (9.6 / 사용량)초마다 1%씩 소모된다 (아무것도 안 할 때 사용량 1)
	// 그 외 2일밤 부터는 고정적으로 추가 전력 소모가 존재
	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curPowerLevel_ <= elecUsageTimer_)
	{
		elecUsageTimer_ = 0.0f;
		curPowerRate_ -= 1.0f;
		UIController_->SetPowerRateRenderer(curPowerRate_);
	}
	// 2일밤 9 %
	// 3일밤 10.8 %
	// 4일밤 13.5 %
	// 5일밤~18 %
	return;
}

void GameController::Update(float _Deltatime)
{
	state_.Update();
	CheckTime();
	CheckElectricityUsage();

	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIPSCENE"))
	{
		// 점프스케어 디버깅 중
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f, -50.0f });
		mainRenderer_->SetChangeAnimation("JumpScareBonnie");
		// 폴더 애니메이션이 순서대로 프레임이 재생되질 않음..
	}
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

	if (curPowerRate_ <= 0.0f)
	{
		return "NoElec";
	}

	if (true == GameEngineInput::GetInst().Down("LDoor_Toggle"))
	{
		if (false == isLdoorClosed_)
		{
			lDoorRenderer_->SetChangeAnimation("LdoorClose");
			isLdoorClosed_ = true;
		}
		else
		{

			lDoorRenderer_->SetChangeAnimation("LdoorOpen");
			isLdoorClosed_ = false;
		}
	}

	if (true == GameEngineInput::GetInst().Down("RDoor_Toggle"))
	{
		if (false == isRdoorClosed_)
		{
			rDoorRenderer_->SetChangeAnimation("RdoorClose");
			isRdoorClosed_ = true;
		}
		else
		{
			rDoorRenderer_->SetChangeAnimation("RdoorOpen");
			isRdoorClosed_ = false;
		}
	}

	if (true == GameEngineInput::GetInst().Down("CCTV_Toggle"))
	{
	
		return "CCTVOpen";
	}

	return StateInfo();
}

StateInfo GameController::startCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션에 앞서 렌더 오더를 새로 정리합니다.
	CCTVRenderer_->On();
	CCTVRenderer_->SetChangeAnimation("CCTVOpen");
	return StateInfo();
}

StateInfo GameController::updateCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션을 여기서 작동 시킵니다.
	// 작동의 짧은 시간동안은 어떤 인풋도 먹히지 않도록 조정합니다.


	if (true == CCTVRenderer_->IsCurAnimationEnd())
	{
		return "CCTV";
	}

	return StateInfo();
}

StateInfo GameController::startCCTV(StateInfo _state)
{
	// CCTV를 작동시킨 상태입니다.
	// 전력 소모량이 1레벨 상승하며,

	
	UIController_->SwitchUIState(PLAYERSTATUS::CCTV);
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{
	if (curTime_ == 6 || curPowerRate_ < 0)
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
	{

	}
		break;
	case LOCATION::LOFFICEDOOR:
	{

	}
		break;
	case LOCATION::ROFFICEDOOR:
	{

	}
		break;
	case LOCATION::SHOWSTAGE:
	{
		CCTVRenderer_->SetImage("ShowStage_Default.png", true);
		// 설정된 스위치에 해당되는 CCTV 화면을 보여줘야 하지만
		// 그냥 셋 이미지가 아닌, "애니메트로닉스의 위치를 측정해 산출한 함수에 의한" 이미지가 셋되어야 한다.
		// 일단 화면에 나오게만 해 보자.
	}
		break;
	case LOCATION::KITCHEN:
	{

	}
		break;
	case LOCATION::BACKSTAGE: 
	{

	}
		break;
	case LOCATION::DININGAREA:
	{

	}
		break;
	case LOCATION::PIRATECOVE:
	{

	}
		break;
	case LOCATION::EASTHALLA:
	{

	}
		break;
	case LOCATION::EASTHALLB:
	{

	}
		break;
	case LOCATION::WESTHALLA:
	{

	}
		break;
	case LOCATION::WESTHALLB:
	{

	}
		break;
	case LOCATION::RESTROOMS:
	{

	}
		break;
	case LOCATION::SUPPLYCLOSET:
	{

	}
		break;
	case LOCATION::NONE:
	{

	}
		break;
	case LOCATION::MAX:
		break;
	default:
		break;
	}

	if (true == GameEngineInput::GetInst().Down("CCTV_Toggle"))
	{
		UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
		return "CCTVClose";
	}

	return StateInfo();
}


StateInfo GameController::startCCTVClose(StateInfo _state)
{
	CCTVRenderer_->SetChangeAnimation("CCTVClose");
	return StateInfo();
}

StateInfo GameController::updateCCTVClose(StateInfo _state)
{
	if (true == CCTVRenderer_->IsCurAnimationEnd())
	{
		mainRenderer_->SetImage("OfficeBasic.png", true);
		CCTVRenderer_->Off();
		return "Idle";
	}


	return StateInfo();
}

StateInfo GameController::startNoElec(StateInfo _state)
{
	UIController_->Off();
	isElecCheckOff_ = true;
	elecUsageTimer_ = 0.0f;

	mainRenderer_->SetImage("NoElecStatic.png", true);
	fanRenderer_->Off();

	if (true == isRdoorClosed_)
	{
		rDoorRenderer_->SetChangeAnimation("RdoorOpen");
		isRdoorClosed_ = false;
	}

	if (true == isLdoorClosed_)
	{
		lDoorRenderer_->SetChangeAnimation("LdoorOpen");
		isLdoorClosed_ = false;

	}

	return StateInfo();
}

StateInfo GameController::updateNoElec(StateInfo _state)
{

// 5초마다 1 / 5 확률로(최대 20초) 노래가 멈추고 화면이 암전된다
// 이후 2초마다 1 / 5 확률로 프레디가 점프스케어

	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (4 == noElecTimerCounter_)
	{
		return "HeisComing";
	}

	if (5.0f <= noElecDeltaTime_)
	{	// 전력이 나간 이후 5초마다 1 / 5 확률로(최대 20초) 노래가 재생되기 시작하고
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "HeisComing";
		}
		break;
		default:
			break;
		}
	}

	return StateInfo();
}


StateInfo GameController::startHeisComing(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	mainRenderer_->SetChangeAnimation("NoElec");
	return StateInfo();
}

StateInfo GameController::updateHeisComing(StateInfo _state)
{
	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (4 == noElecTimerCounter_)
	{
		return "HeKillsYou";
	}

	if (5.0f <= noElecDeltaTime_)
	{	// 전력이 나간 이후 5초마다 1 / 5 확률로(최대 20초) 노래가 재생되기 시작하고
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "HeKillsYou";
		}
		break;
		default:
			break;
		}
	}
	return StateInfo();
}

StateInfo GameController::startHeKillsYou(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;
	mainRenderer_->SetChangeAnimation("NoElecBlink");
	return StateInfo();
}

StateInfo GameController::updateHeKillsYou(StateInfo _state)
{
	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (2.0f <= noElecDeltaTime_)
	{
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "NoElecDeath";
		}
		break;
		default:
			break;
		}
	}
	return StateInfo();
	return StateInfo();
}

StateInfo GameController::startNoElecDeath(StateInfo _state)
{
	mainRenderer_->SetChangeAnimation("NoElecFreddy");
	return StateInfo();
}

StateInfo GameController::updateNoElecDeath(StateInfo _state)
{
	if (true == mainRenderer_->IsCurAnimationEnd())
	{
		GetLevel()->RequestLevelChange("GameOver");
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

