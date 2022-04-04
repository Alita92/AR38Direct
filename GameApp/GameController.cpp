#include "PreCompile.h"
#include "GameController.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// UIController
#include "UIController.h"
#include "FadeScreen.h"
#include "GlitchScreen.h"

// Enemy AI
#include "AIBonnie.h"
#include "AIChica.h"
#include "AIFoxy.h"
#include "AIFreddy.h"

GameController::GameController() // default constructer 디폴트 생성자
	: CurPlayerState_(PLAYERSTATUS::OFFICE)
	, CurCCTVState_(LOCATION::SHOWSTAGE)
	, elecUsageTimer_(0.0f)
	, state_(this)
	, curPowerLevel_(0)
	, curPowerRate_(0.0f)
	, isElecCheckOff_(false)
	, aiBonnie_(nullptr)
	, aiChica_(nullptr)
	, aiFoxy_(nullptr)
	, aiFreddy_(nullptr)
	, curTime_(0)
	, timeUsageTimer_(0.0f)
	, isTimeCheckOff_(false)
	, curDay_(0)
	, isLdoorClosed_(false)
	, isLdoorLighted_(false)
	, isRdoorClosed_(false)
	, isRdoorLighted_(false)
	, noElecDeltaTime_(0.0f)
	, noElecTimerCounter_(0)
	, playDeadTimer_(0.0f)
	, deathSceneTimer_(0.0f)
	, PrevCCTVState_(LOCATION::MAX)
	, fadeScreen_(nullptr)
	, UIController_(nullptr)
	, rDoorRenderer_(nullptr)
	, lDoorRenderer_(nullptr)
	, mainRenderer_(nullptr)
	, glitchScreen_(nullptr)
	, fanRenderer_(nullptr)
	, CCTVRealRenderer_(nullptr)
	, CCTVAnimationRenderer_(nullptr)
	, foxyRunningRenderer_(nullptr)
	, foxyDeathTimer_(0.0f)
	, isPirateCoveChecked_(false)
	, isFoxyRunning_(false)
	, isAnomalyOn_(false)
	, anomalyDice_(0)
	, bonnieDice_(0)
	, chicaDice_(0)
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
	
	state_.CreateState("BonnieDeath", &GameController::startBonnieDeath, &GameController::updateBonnieDeath);
	state_.CreateState("ChicaDeath", &GameController::startChicaDeath, &GameController::updateChicaDeath);
	state_.CreateState("FoxyDeath", &GameController::startFoxyDeath, &GameController::updateFoxyDeath);

	state_.CreateState("NoElec", &GameController::startNoElec, &GameController::updateNoElec);
	state_.CreateState("HeisComing", &GameController::startHeisComing, &GameController::updateHeisComing);
	state_.CreateState("HeKillsYou", &GameController::startHeKillsYou, &GameController::updateHeKillsYou);
	state_.CreateState("NoElecDeath", &GameController::startNoElecDeath, &GameController::updateNoElecDeath);

	state_.CreateState("Win", &GameController::startWin, &GameController::updateWin);

	state_.ChangeState("Idle");
}

void GameController::InitPlayStatus()
{
	CurPlayerState_ = PLAYERSTATUS::OFFICE;
	CurCCTVState_ = LOCATION::SHOWSTAGE;
	curPowerLevel_ = 1;
	curPowerRate_ = MAX_ELECTRICITIY_RATE;
	curTime_ = 0;
	curDay_ = 1;
}

void GameController::InitEnemy()
{
	aiBonnie_ = GetLevel()->CreateActor<AIBonnie>();
	aiBonnie_->SetAILevel(4);
	aiChica_ = GetLevel()->CreateActor<AIChica>();
	aiChica_->SetAILevel(4);
	aiFoxy_ = GetLevel()->CreateActor<AIFoxy>();
	aiFoxy_->SetAILevel(20);
	aiFreddy_ = GetLevel()->CreateActor<AIFreddy>();
	aiFreddy_->SetAILevel(20);
}

void GameController::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::BACKGROUND1)});

		mainRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
		mainRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f, true);
		mainRenderer_->CreateAnimationFolder("JumpScareFoxy", "JumpScareFoxy", 0.03f, false);
		mainRenderer_->CreateAnimationFolder("JumpScareFreddy", "JumpScareFreddy", 0.03f, false);

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
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorClose", 0, 14, 0.04f, false);
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorOpen", 14, 0, 0.04f, false);
	}

	{		
		CCTVAnimationRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVAnimationRenderer_->SetImage("ShowStage_Default.png", true);
		CCTVAnimationRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT0) });
		CCTVAnimationRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVOpen", 0, 9, 0.033f, false);
		CCTVAnimationRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVClose", 9, 0, 0.033f, false);
		CCTVAnimationRenderer_->Off();
	}

	{
		CCTVRealRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVRealRenderer_->SetImage("ShowStage_Default.png", true);

		CCTVRealRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::CCTV0) });
		CCTVRealRenderer_->Off();
	}

	{
		foxyRunningRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		foxyRunningRenderer_->SetImage("WestHallA_Default.png", true);
		foxyRunningRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::CCTV1) });
		foxyRunningRenderer_->CreateAnimationFolder("RunningFoxy", "RunningFoxy", 0.04f, false);
		foxyRunningRenderer_->Off();
	}
}

void GameController::InitScreenEffects()
{
	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(1.0f);
	fadeScreen_->SetLoadingRenderer();
	fadeScreen_->OffScreen(0.7f);

	glitchScreen_ = GetLevel()->CreateActor<GlitchScreen>();
	glitchScreen_->SetWhiteNoiseAlpha(0.3f);
}

void GameController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f ,0.0f, 10.0f });

	InitUIController();
	InitScreenEffects();
	InitEnemy();
	InitState();
	InitAnimation();
	InitPlayStatus();
	
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
	UIController_->SetPowerLevelRenderer(curPowerLevel_);
	return;
}

void GameController::Update(float _Deltatime)
{
	state_.Update();
	CheckTime();
	CheckElectricityUsage();
}


void GameController::CheckOfficeInput()
{
	if (true == GameEngineInput::GetInst().Down("LDoor_Toggle") && true == lDoorRenderer_->IsCurAnimationEnd())
	{
		if (false == isLdoorClosed_)
		{
			isLdoorClosed_ = true;
			aiBonnie_->isDoorLocked_ = true;
			aiFoxy_->isDoorLocked_ = true;
			curPowerLevel_ += 1;
		}
		else
		{
			isLdoorClosed_ = false;
			aiBonnie_->isDoorLocked_ = false;
			aiFoxy_->isDoorLocked_ = false;
			curPowerLevel_ -= 1;
		}
	}

	if (true == GameEngineInput::GetInst().Down("RDoor_Toggle") && true == rDoorRenderer_->IsCurAnimationEnd())
	{
		if (false == isRdoorClosed_)
		{
			isRdoorClosed_ = true;
			aiChica_->isDoorLocked_ = true;
			aiFreddy_->isDoorLocked_ = true;
			curPowerLevel_ += 1;

		}
		else
		{
			isRdoorClosed_ = false;
			aiChica_->isDoorLocked_ = false;
			aiFreddy_->isDoorLocked_ = false;
			curPowerLevel_ -= 1;
		}
	}

	if (true == GameEngineInput::GetInst().Down("LLight_Toggle"))
	{
		if (false == isLdoorLighted_)
		{
			isLdoorLighted_ = true;

			if (true == isRdoorLighted_)
			{
				isRdoorLighted_ = false;
				curPowerLevel_--;
			}
			curPowerLevel_++;

		}
		else
		{
			isLdoorLighted_ = false;
			curPowerLevel_ -= 1;
		}
	}

	if (true == GameEngineInput::GetInst().Down("RLight_Toggle"))
	{
		if (false == isRdoorLighted_)
		{
			isRdoorLighted_ = true;
			if (true == isLdoorLighted_)
			{
				isLdoorLighted_ = false;
				curPowerLevel_--;
			}
			curPowerLevel_ += 1;

		}
		else
		{
			isRdoorLighted_ = false;
			curPowerLevel_ -= 1;
		}
	}
}

StateInfo GameController::startIdle(StateInfo _state)
{
	{
		// cctv를 보고 있지 않다
		// AI 에게 인지시켜 주는 겁니다.
		aiBonnie_->isPlayerStares_ = true;
		aiChica_->isPlayerStares_ = true;
		aiFoxy_->isPlayerStares_ = false;

	}

	CurPlayerState_ = PLAYERSTATUS::OFFICE;
	return StateInfo();
}

StateInfo GameController::updateIdle(StateInfo _state)
{
	CheckOfficeInput();

	if (curTime_ == 6)
	{
		return "Win";
	}

	if (curPowerRate_ <= 0.0f)
	{
		return "NoElec";
	}

	if (LOCATION::OFFICE == aiFreddy_->GetLocation())
	{
		return "FreddyDeath";
	}

	if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel())
	{
		if (true == isPirateCoveChecked_)
		{
			foxyDeathTimer_ += GameEngineTime::GetInst().GetDeltaTime();

			if (1.5f <= foxyDeathTimer_)
			{
				if (false == isLdoorClosed_)
				{
					foxyDeathTimer_ = 0.0f;
					return "FoxyDeath";
				}
				else
				{
					curPowerRate_ -= (5.0f * static_cast<float>(curDay_));
					// 문 두들기는 사운드 재생
					isPirateCoveChecked_ = false;
					isFoxyRunning_ = false;
					foxyDeathTimer_ = 0.0f;
					aiFoxy_->ResetFoxyLevel();
				}
			}
		}
		else
		{
			foxyDeathTimer_ += GameEngineTime::GetInst().GetDeltaTime();

			if (2.0f <= foxyDeathTimer_ )
			{
				if (false == isLdoorClosed_)
				{
					foxyDeathTimer_ = 0.0f;
					return "FoxyDeath";
				}
				else
				{
					curPowerRate_ -= (5.0f * static_cast<float>(curDay_));
					// 문 두들기는 사운드 재생
					isPirateCoveChecked_ = false;
					foxyDeathTimer_ = 0.0f;
					aiFoxy_->ResetFoxyLevel();
					isFoxyRunning_ = false;
				}
			}
		}
	}


	if (false == isLdoorClosed_)
	{
		lDoorRenderer_->SetChangeAnimation("LdoorOpen");
	}
	else if (true == isLdoorClosed_)
	{
		lDoorRenderer_->SetChangeAnimation("LdoorClose");
	}

	if (false == isRdoorClosed_)
	{
		rDoorRenderer_->SetChangeAnimation("RdoorOpen");
	}
	else if (true == isRdoorClosed_)
	{
		rDoorRenderer_->SetChangeAnimation("RdoorClose");
	}

	if (true == isLdoorLighted_)
	{
		if (LOCATION::LOFFICEDOOR == aiBonnie_->GetLocation())
		{
			mainRenderer_->SetImage("OfficeLightL1.png", true);
		}
		else
		{
			mainRenderer_->SetImage("OfficeLightL0.png", true);
		}
	}
	else if (false == isLdoorLighted_ && false == isRdoorLighted_)
	{
		mainRenderer_->SetImage("OfficeBasic.png", true);
	}

	if (true == isRdoorLighted_)
	{
		if (LOCATION::ROFFICEDOOR == aiChica_->GetLocation())
		{
			mainRenderer_->SetImage("OfficeLightR1.png", true);
		}
		else
		{
			mainRenderer_->SetImage("OfficeLightR0.png", true);
		}
	}
	else if (false == isRdoorLighted_ && false == isLdoorLighted_)
	{
		mainRenderer_->SetImage("OfficeBasic.png", true);
	}
	
	UIController_->CCTVButtonCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCCTVButton, this, std::placeholders::_1));

	return StateInfo();
}

StateInfo GameController::startCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션에 앞서 렌더 오더를 새로 정리합니다.
	curPowerLevel_ += 1;
	CCTVAnimationRenderer_->On();
	CCTVAnimationRenderer_->SetChangeAnimation("CCTVOpen");
	return StateInfo();
}

StateInfo GameController::updateCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션을 여기서 작동 시킵니다.
	// 작동의 짧은 시간동안은 어떤 인풋도 먹히지 않도록 조정합니다.

	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		return "CCTV";
	}

	return StateInfo();
}

StateInfo GameController::startCCTV(StateInfo _state)
{
	// CCTV를 작동시킨 상태입니다.
	// 전력 소모량이 1레벨 상승하며,
	glitchScreen_->PlayWhiteNoise(true);
	glitchScreen_->PlayAwakeScanLineFast();
	fanRenderer_->Off();
	CCTVAnimationRenderer_->Off();
	CurPlayerState_ = PLAYERSTATUS::CCTV;

	bonnieDice_ = randomGenerator_.RandomInt(0, 1);
	chicaDice_ = randomGenerator_.RandomInt(0, 1);
	isAnomalyOn_ = randomGenerator_.RandomBool(25.0f / 100.0f);
	anomalyDice_ = randomGenerator_.RandomInt(0, 3);


	{
		// 보니, 치카 AI 에게 이제 공격해도 된다는 신호를 줍니다.
		aiBonnie_->isPlayerStares_ = false;
		aiChica_->isPlayerStares_ = false;

		// 폭시는 접근 못 한다고 신호 줍니다.
		aiFoxy_->isPlayerStares_ = true;
	}

	UIController_->SwitchUIState(PLAYERSTATUS::CCTV);
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{
	if (LOCATION::OFFICE == aiBonnie_->GetLocation())
	{
		playDeadTimer_ += GameEngineTime::GetInst().GetDeltaTime();

		if (MAXIMUM_PLAYDEAD_DURATION <= playDeadTimer_)
		{
			return "BonnieDeath";
		}
	}

	if (LOCATION::OFFICE == aiChica_->GetLocation())
	{
		playDeadTimer_ += GameEngineTime::GetInst().GetDeltaTime();

		if (MAXIMUM_PLAYDEAD_DURATION <= playDeadTimer_)
		{
			return "ChicaDeath";
		}
	}

	if (curPowerRate_ <= 0)
	{
		// 시간, 전기 하나라도 조건 충족 시 강제로 CCTV 모드가 해제됩니다.
		// 이후는 Idle 에서 처리해줍니다.
		return "NoElec";
	}

	switch (CurCCTVState_)
	{
		// 현 CCTV가 어디를 지향했는지에 따라
		// 화면을 바꿔 보여줍니다.
	case LOCATION::SHOWSTAGE:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation() && LOCATION::SHOWSTAGE != aiFreddy_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("ShowStage_AllGone.png", true);
			break;
		}

		if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation() && LOCATION::SHOWSTAGE == aiFreddy_->GetLocation())
		{
			if (true == isAnomalyOn_)
			{
				CCTVRealRenderer_->SetImage("ShowStage_BCGone_Anomaly.png", true);
				if (false == aiFreddy_->isBonnieChica0ut_)
				{
					aiFreddy_->isBonnieChica0ut_ = true;
				}

				break;
			}

			CCTVRealRenderer_->SetImage("ShowStage_BCGone.png", true);
			if (false == aiFreddy_->isBonnieChica0ut_)
			{
				aiFreddy_->isBonnieChica0ut_ = true;
			}
			break;
		}
		else if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE == aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("ShowStage_BonnieGone.png", true);
			break;
		}
		else if (LOCATION::SHOWSTAGE == aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("ShowStage_ChicaGone.png", true);
			break;
		}

		if (true == isAnomalyOn_)
		{
			CCTVRealRenderer_->SetImage("ShowStage_Default_Anomaly.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("ShowStage_Default.png", true);
	}
		break;
	case LOCATION::KITCHEN:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();
	
		CCTVRealRenderer_->SetImage("Kitchen.png", true);
	}
		break;
	case LOCATION::BACKSTAGE: 
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::BACKSTAGE == aiBonnie_->GetLocation())
		{
			switch (bonnieDice_)
			{
			case 0:
				CCTVRealRenderer_->SetImage("BackStage_Bonnie0.png", true);
				break;
			case 1:
				CCTVRealRenderer_->SetImage("BackStage_Bonnie1.png", true);
				break;
			default:
				break;
			}
			break;
		}
		
		if (true == isAnomalyOn_)
		{
			CCTVRealRenderer_->SetImage("BackStage_Anomaly.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("BackStage_Default.png", true);
	}
		break;
	case LOCATION::DININGAREA:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::DININGAREA == aiBonnie_->GetLocation() && LOCATION::DININGAREA == aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("DiningArea_Chica1.png", true);
			break;
		}
		else if (LOCATION::DININGAREA == aiBonnie_->GetLocation() && LOCATION::DININGAREA != aiChica_->GetLocation())
		{
			switch (bonnieDice_)
			{
			case 0:
				CCTVRealRenderer_->SetImage("DiningArea_Bonnie0.png", true);
				break;
			case 1:
				CCTVRealRenderer_->SetImage("DiningArea_Bonnie1.png", true);
				break;
			default:
				break;
			}
			break;
		}
		else if (LOCATION::DININGAREA != aiBonnie_->GetLocation() && LOCATION::DININGAREA == aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("DiningArea_Chica0.png", true);
			break;
		}
		else if (LOCATION::DININGAREA == aiFreddy_->GetLocation() && LOCATION::DININGAREA != aiBonnie_->GetLocation() && LOCATION::DININGAREA != aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("DiningArea_Freddy.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("DiningArea_Default.png", true);
	}
		break;
	case LOCATION::PIRATECOVE:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		FOXYLEVEL curFoxyLevel = aiFoxy_->GetFoxyLevel();

		switch (curFoxyLevel)
		{
		case FOXYLEVEL::LV1:
			CCTVRealRenderer_->SetImage("PirateCove_Lv1.png", true);
			break;
		case FOXYLEVEL::LV2:
			CCTVRealRenderer_->SetImage("PirateCove_Lv2.png", true);
			break;
		case FOXYLEVEL::LV3:
			CCTVRealRenderer_->SetImage("PirateCove_Lv3.png", true);
			break;
		case FOXYLEVEL::LV4:
		{
			//isPirateCoveChecked_ = true;
			if (true == randomGenerator_.RandomBool(5.0f / 100.0f))
			{
				CCTVRealRenderer_->SetImage("PirateCove_Lv4_Anomaly.png", true);
			}
			CCTVRealRenderer_->SetImage("PirateCove_Lv4.png", true);
		}
			break;
		case FOXYLEVEL::MAX:
			break;
		default:
			break;
		}
	}
		break;
	case LOCATION::EASTHALLA:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::EASTHALLA == aiChica_->GetLocation())
		{
			switch (chicaDice_)
			{
			case 0:
				CCTVRealRenderer_->SetImage("EastHallA_Chica0.png", true);
				break;
			case 1:
				CCTVRealRenderer_->SetImage("EastHallA_Chica1.png", true);
				break;
			default:
				break;
			}
			break;
		}
		else if (LOCATION::EASTHALLA != aiChica_->GetLocation() && LOCATION::EASTHALLA == aiFreddy_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("EastHallA_Freddy.png", true);
			break;
		}

		if (true == isAnomalyOn_)
		{
			switch (anomalyDice_)
			{
			case 0:
			case 1:
				CCTVRealRenderer_->SetImage("EastHallA_Anomaly0.png", true);
				break;
			case 2:
			case 3:
				CCTVRealRenderer_->SetImage("EastHallA_Anomaly1.png", true);
				break;

			default:
				break;
			}
			break;
		}
		CCTVRealRenderer_->SetImage("EastHallA_Default.png", true);
	}
		break;

	case LOCATION::EASTHALLB:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::EASTHALLB == aiFreddy_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("EastHallB_Freddy.png", true);
			break;	
		}
		else if (LOCATION::EASTHALLB == aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("EastHallB_Chica0.png", true);
			break;
		}


		if (true == isAnomalyOn_)
		{
			switch (anomalyDice_)
			{
			case 0:
				CCTVRealRenderer_->SetImage("EastHallB_Anomaly0.png", true);
				break;
			case 1:
				CCTVRealRenderer_->SetImage("EastHallB_Anomaly1.png", true);
				break;
			case 2:
				CCTVRealRenderer_->SetImage("EastHallB_Anomaly2.png", true);
				break;
			case 3:
				CCTVRealRenderer_->SetImage("EastHallB_Anomaly3.png", true);
				break;
			default:
				break;
			}
			break;
		}
		CCTVRealRenderer_->SetImage("EastHallB_Default.png", true);
	}
		break;
	case LOCATION::WESTHALLA:
	{
		if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel() && false == isFoxyRunning_)
		{
			isFoxyRunning_ = true;
			foxyRunningRenderer_->On();
			foxyRunningRenderer_->SetChangeAnimation("RunningFoxy", true);
			CCTVRealRenderer_->Off();
			break;
		}
		else if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel() && true == isFoxyRunning_)
		{
			break;
		}
		
			CCTVRealRenderer_->On();
			foxyRunningRenderer_->Off();

			if (LOCATION::WESTHALLA == aiBonnie_->GetLocation())
			{
				CCTVRealRenderer_->SetImage("WestHallA_Bonnie.png", true);
				break;
			}

			CCTVRealRenderer_->SetImage("WestHallA_Default.png", true);
		
	}
		break;
	case LOCATION::WESTHALLB:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::WESTHALLB == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("WestHallB_Bonnie0.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("WestHallB_Default.png", true);
	}
		break;
	case LOCATION::RESTROOMS:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::RESTROOMS == aiChica_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("RestRooms_Chica0.png", true);
			break;
		}
		else if (LOCATION::RESTROOMS == aiFreddy_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("RestRooms_Freddy.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("RestRooms_Default.png", true);
	}
		break;
	case LOCATION::SUPPLYCLOSET:
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();

		if (LOCATION::SUPPLYCLOSET == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("SuppltCloset_Bonnie.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("SupplyCloset_Default.png", true);
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

	UIController_->SetCCTVNameRenderer(CurCCTVState_);
	UIController_->SetCCTVScreenLowlight(PrevCCTVState_);
	UIController_->SetCCTVScreenHighlight(CurCCTVState_);

	{
		UIController_->CCTVButtonCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCCTVButton, this, std::placeholders::_1));
		UIController_->cam1ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1A, this, std::placeholders::_1));
		UIController_->cam1BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1B, this, std::placeholders::_1));
		UIController_->cam1CCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1C, this, std::placeholders::_1));
		UIController_->cam5Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam5, this, std::placeholders::_1));
		UIController_->cam3Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam3, this, std::placeholders::_1));
		UIController_->cam2ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam2A, this, std::placeholders::_1));
		UIController_->cam2BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam2B, this, std::placeholders::_1));
		UIController_->cam7Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam7, this, std::placeholders::_1));
		UIController_->cam6Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam6, this, std::placeholders::_1));
		UIController_->cam4ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam4A, this, std::placeholders::_1));
		UIController_->cam4BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam4B, this, std::placeholders::_1));
	}


	// 디버그 임시
	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIP"))
	{
		CCTVRealRenderer_->Off();
		foxyRunningRenderer_->On();
		foxyRunningRenderer_->SetChangeAnimation("RunningFoxy", true);
	}
	if (true == GameEngineInput::GetInst().Down("ESC"))
	{
		foxyRunningRenderer_->Off();
		CCTVRealRenderer_->On();
	}


	return StateInfo();
}


StateInfo GameController::startCCTVClose(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	curPowerLevel_ -= 1;
	CCTVRealRenderer_->Off();
	foxyRunningRenderer_->Off();
	CCTVAnimationRenderer_->On();
	if (curPowerRate_ != 0.0f)
	{
		fanRenderer_->On();
	}

	aiBonnie_->isPlayerStares_ = true;
	aiChica_->isPlayerStares_ = true;
	aiFoxy_->isPlayerStares_ = false;

	CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	return StateInfo();
}

StateInfo GameController::updateCCTVClose(StateInfo _state)
{
	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		if (curPowerRate_ != 0)
		{
			mainRenderer_->SetImage("OfficeBasic.png", true);
		}

		CCTVAnimationRenderer_->Off();

		return "Idle";
	}
	return StateInfo();
}

StateInfo GameController::startBonnieDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	CCTVRealRenderer_->Off();
	CCTVAnimationRenderer_->On();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	mainRenderer_->SetChangeAnimation("JumpScareBonnie", true);

	lDoorRenderer_->Off();
	rDoorRenderer_->Off();

	UIController_->Off();
	return StateInfo();
}

StateInfo GameController::updateBonnieDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		CCTVAnimationRenderer_->Off();
	}

	if (0.88f <= deathSceneTimer_)
	{
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startChicaDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	CCTVRealRenderer_->Off();
	CCTVAnimationRenderer_->On();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	mainRenderer_->SetChangeAnimation("JumpScareChica", true);
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();

	UIController_->Off();
	return StateInfo();
}

StateInfo GameController::updateChicaDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		CCTVAnimationRenderer_->Off();
	}

	if (0.88f <= deathSceneTimer_)
	{
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startFoxyDeath(StateInfo _state)
{
	isFoxyRunning_ = false;
	glitchScreen_->PlayWhiteNoise(false);
	CCTVRealRenderer_->Off();
	CCTVAnimationRenderer_->Off();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	mainRenderer_->SetChangeAnimation("JumpScareFoxy", true);
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();

	UIController_->Off();
	return StateInfo();
}

StateInfo GameController::updateFoxyDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (0.88f <= deathSceneTimer_)
	{
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startFreddyDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	CCTVRealRenderer_->Off();
	CCTVAnimationRenderer_->Off();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	mainRenderer_->SetChangeAnimation("JumpScareFreddy", true);
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();

	UIController_->Off();

	return StateInfo();
}

StateInfo GameController::updateFreddyDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (0.88f <= deathSceneTimer_)
	{
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}


StateInfo GameController::startNoElec(StateInfo _state)
{
	UIController_->Off();

	if (CurPlayerState_ != PLAYERSTATUS::OFFICE)
	{
		CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
		CCTVRealRenderer_->Off();
	}
	
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




void GameController::CollisionCCTVButton(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		// 닿았으면 바로 전환 가능하게
		if (PLAYERSTATUS::OFFICE != CurPlayerState_)
		{
			if (LOCATION::OFFICE == aiBonnie_->GetLocation())
			{
				UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
				state_.ChangeState("BonnieDeath");
				return;
			}
			else if (LOCATION::OFFICE == aiChica_->GetLocation())
			{
				UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
				state_.ChangeState("ChicaDeath");
				return;
			}


			UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
			state_.ChangeState("CCTVClose");
			return;
		}
		state_.ChangeState("CCTVOpen");
		return;
	}


	return;
}


void GameController::CollisionMuteCall(GameEngineCollision* _other)
{

}

void GameController::CollisionCam1A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::SHOWSTAGE;
	}
}

void GameController::CollisionCam1B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::DININGAREA;
	}
}

void GameController::CollisionCam1C(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::PIRATECOVE;
	}
}

void GameController::CollisionCam3(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::SUPPLYCLOSET;
	}
}

void GameController::CollisionCam5(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::BACKSTAGE;
	}
}

void GameController::CollisionCam2A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::WESTHALLA;
	}
}

void GameController::CollisionCam2B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::WESTHALLB;
	}
}

void GameController::CollisionCam7(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::RESTROOMS;
	}
}

void GameController::CollisionCam6(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::KITCHEN;
	}
}

void GameController::CollisionCam4A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::EASTHALLA;
	}
}
void GameController::CollisionCam4B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::EASTHALLB;
	}
}
