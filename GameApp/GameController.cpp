#include "PreCompile.h"
#include "GameController.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineBackgroundRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>

// UIController
#include "UIController.h"
#include "FadeScreen.h"
#include "GlitchScreen.h"
#include "GameMouse.h"

// Enemy AI
#include "AIBonnie.h"
#include "AIChica.h"
#include "AIFoxy.h"
#include "AIFreddy.h"

#include "GameStaticData.h"

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
	, curDay_(DAY::MAX)
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
	, rSwitchRenderer_(nullptr)
	, lSwitchRenderer_(nullptr)
	, mainRenderer_(nullptr)
	, jumpScareRenderer_(nullptr)
	, glitchScreen_(nullptr)
	, fanRenderer_(nullptr)
	, foxyDeathTimer_(0.0f)
	, freddyDeathTimer_(0.0f)
	, isPirateCoveChecked_(false)
	, isFoxyRunning_(false)
	, isAnomalyOn_(false)
	, anomalyDice_(0)
	, bonnieDice_(0)
	, chicaDice_(0)
	, winDeltaTime_(0.0f)
	, alphaChangeTime_(0.0f)
	, gameMouse_(nullptr)
	, alphaChangeTime1_(2.0f)
	, isPhoneStop_(false)
	, isCCTVGlitched_(false)
	, CCTVGlitchDeltaTime_(0.0f)
	, isLoadingDone_(false)
	, flag1_(false)
	, flag2_(false)
	, flag3_(false)
	, flag4_(false)
	, lSwitchDoorCollision_(nullptr)
	, lSwitchLightCollision_(nullptr)
	, rSwitchDoorCollision_(nullptr)
	, rSwitchLightCollision_(nullptr)
	, CCTVMoveDeltaTime_(0.0f)
	, isCCTVFullyTilted_(false)
	, CCTVMoveFlag_(false)
	, subtitleDeltatime_(0.0f)
	, subtitleIndex_(0)
	, isFadeIn_(false)
	, firstLoadingDeltatime_(0.0f)
	, isMuted_(false)
	, freddyNoseCollison_(nullptr)
	, isDebugOn_(false)
{

}

GameController::~GameController() // default destructer 디폴트 소멸자
{

}

void GameController::InitUIController()
{
	UIController_ = GetLevel()->CreateActor<UIController>();
	UIController_->SetNightTypo(GameStaticData::curDay_);
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
	state_.CreateState("FreddyDeath", &GameController::startFreddyDeath, &GameController::updateFreddyDeath);

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
	curDay_ = GameStaticData::curDay_;
}

void GameController::InitEnemy()
{
	aiBonnie_ = GetLevel()->CreateActor<AIBonnie>();
	aiChica_ = GetLevel()->CreateActor<AIChica>();
	aiFoxy_ = GetLevel()->CreateActor<AIFoxy>();
	aiFreddy_ = GetLevel()->CreateActor<AIFreddy>();
}

void GameController::InitEnemyAILevel()
{
	switch (GameStaticData::curDay_)
	{
	case DAY::DAY1:
	{
		aiBonnie_->SetAILevel(5);
		aiChica_->SetAILevel(5);
		aiFoxy_->SetAILevel(5);
		aiFreddy_->SetAILevel(3);
	}
	break;
	case DAY::DAY2:
	{
		aiBonnie_->SetAILevel(3);
		aiChica_->SetAILevel(1);
		aiFoxy_->SetAILevel(1);
		aiFreddy_->SetAILevel(0);
	}
	break;
	case DAY::DAY3:
	{
		aiBonnie_->SetAILevel(0);
		aiChica_->SetAILevel(5);
		aiFoxy_->SetAILevel(2);
		aiFreddy_->SetAILevel(1);
	}
	break;
	case DAY::DAY4:
	{
		aiBonnie_->SetAILevel(2);
		aiChica_->SetAILevel(4);
		aiFoxy_->SetAILevel(6);
		aiFreddy_->SetAILevel(2);
	}
	break;
	case DAY::DAY5:
	{
		aiBonnie_->SetAILevel(5);
		aiChica_->SetAILevel(7);
		aiFoxy_->SetAILevel(5);
		aiFreddy_->SetAILevel(3);
	}
	break;
	case DAY::DAY6:
	{

	}
	break;
	case DAY::CUSTOM:
	{
		aiBonnie_->SetAILevel(GameStaticData::AICustomStartLevelBonnie_);
		aiChica_->SetAILevel(GameStaticData::AICustomStartLevelChica_);
		aiFoxy_->SetAILevel(GameStaticData::AICustomStartLevelFoxy_);
		aiFreddy_->SetAILevel(GameStaticData::AICustomStartLevelFreddy_);
	}
		break;
	case DAY::MAX:
		break;
	default:
		break;
	}
}

void GameController::AICheck()
{
	if (1 == curTime_ && false == flag1_)
	{
		aiBonnie_->AddAILevel(1);
		flag1_ = true;
	}

	if (2 == curTime_ && false == flag2_)
	{
		aiBonnie_->AddAILevel(1);
		flag2_ = true;

	}

	if (3 == curTime_ && false == flag3_)
	{
		aiBonnie_->AddAILevel(1);
		aiChica_->AddAILevel(1);
		aiFoxy_->AddAILevel(1);
		flag3_ = true;
	}

	if (4 == curTime_ && false == flag4_)
	{
		aiBonnie_->AddAILevel(1);
		aiChica_->AddAILevel(1);
		aiFoxy_->AddAILevel(1);
		flag4_ = true;
	}
}

void GameController::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::BACKGROUND1)});
	}

	{
		jumpScareRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		jumpScareRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<float>(RenderOrder::JUMPSCARE) });
		jumpScareRenderer_->SetImage("OfficeBasic.png", true);


		jumpScareRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
		jumpScareRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f, true);
		jumpScareRenderer_->CreateAnimationFolder("JumpScareFoxy", "JumpScareFoxy", 0.03f, false);
		jumpScareRenderer_->CreateAnimationFolder("JumpScareFreddy", "JumpScareFreddy", 0.03f, false);

		jumpScareRenderer_->CreateAnimationFolder("NoElec", "NoElec", 0.04f, true);
		jumpScareRenderer_->CreateAnimationFolder("NoElecBlink", "NoElecBlink", 0.04f, false);
		jumpScareRenderer_->CreateAnimationFolder("NoElecFreddy", "NoElecFreddy", 0.04f, false);

		jumpScareRenderer_->Off();

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
		lDoorRenderer_->GetTransform()->SetLocalPosition({ -615.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1)});
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorClose", 14, 0, 0.04f, false);
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorOpen", 0, 14, 0.04f, false);
	}

	{
		rSwitchRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		rSwitchRenderer_->SetImage("SwitchR_00.png", true);
		rSwitchRenderer_->GetTransform()->SetLocalPosition({ 730.0f, 0.0f, static_cast<float>(RenderOrder::SWITCH) });
	}

	{
		lSwitchRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		lSwitchRenderer_->SetImage("SwitchL_00.png", true);
		lSwitchRenderer_->GetTransform()->SetLocalPosition({ -760.0f, 0.0f, static_cast<float>(RenderOrder::SWITCH) });
	}

	{
		rDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 595.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1) });
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorClose", 0, 14, 0.04f, false);
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorOpen", 14, 0, 0.04f, false);
	}
}

void GameController::InitScreenEffects()
{
	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(1.0f);
	fadeScreen_->SetLoadingRenderer();
	
	glitchScreen_ = GetLevel()->CreateActor<GlitchScreen>();
	glitchScreen_->SetWhiteNoiseAlpha(0.3f);
}

void GameController::InitSwitchCollision()
{
	{
		lSwitchDoorCollision_ = CreateTransformComponent<GameEngineCollision>();
		lSwitchDoorCollision_->GetTransform()->SetLocalPosition({-760.0f, 55.0f, 0.0f});
		lSwitchDoorCollision_->GetTransform()->SetLocalScaling({ 60.0f, 80.0f, 1.0f });
		lSwitchDoorCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::GAMEACTOR));
		
		lSwitchLightCollision_ = CreateTransformComponent<GameEngineCollision>();
		lSwitchLightCollision_->GetTransform()->SetLocalPosition({-760.0f, -52.0f, 0.0f});
		lSwitchLightCollision_->GetTransform()->SetLocalScaling({ 60.0f, 80.0f, 1.0f });
		lSwitchLightCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::GAMEACTOR));
	}	
		
	{	
		rSwitchDoorCollision_ = CreateTransformComponent<GameEngineCollision>();
		rSwitchDoorCollision_->GetTransform()->SetLocalPosition({ 730.0f, 55.0f,0.0f});
		rSwitchDoorCollision_->GetTransform()->SetLocalScaling({ 60.0f, 80.0f, 1.0f });
		rSwitchDoorCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::GAMEACTOR));
		
		rSwitchLightCollision_ = CreateTransformComponent<GameEngineCollision>();
		rSwitchLightCollision_->GetTransform()->SetLocalPosition({ 730.0f, -52.0f,0.0f });
		rSwitchLightCollision_->GetTransform()->SetLocalScaling({ 60.0f, 80.0f, 1.0f });
		rSwitchLightCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::GAMEACTOR));
	}

	{
		freddyNoseCollison_ = CreateTransformComponent<GameEngineCollision>();
		freddyNoseCollison_->GetTransform()->SetLocalPosition({-120.0f, 130.0f, 0.0f});
		freddyNoseCollison_->GetTransform()->SetLocalScaling({ 10.0f, 10.0f, 1.0f });
		freddyNoseCollison_->SetCollisionGroup(static_cast<int>(InGameCollisonType::GAMEACTOR));
	}
}

void GameController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f ,0.0f, 10.0f });

	gameMouse_ = GetLevel()->CreateActor<GameMouse>();
	gameMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));

	InitUIController();
	InitScreenEffects();
	InitEnemy();
	InitEnemyAILevel();
	InitState();
	InitAnimation();
	InitPlayStatus();
	InitSwitchCollision();

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P');
	}
	
}

void GameController::ControllerReloading()
{
	state_.ChangeState("Idle");

	aiBonnie_->Reloading();
	aiChica_->Reloading();
	aiFoxy_->Reloading();
	aiFreddy_->Reloading();

	aiBonnie_->On();
	aiChica_->On();
	aiFoxy_->On();
	aiFreddy_->On();

	gameMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));

	{
		CurPlayerState_ = PLAYERSTATUS::OFFICE;
		CurCCTVState_ = LOCATION::SHOWSTAGE;
		curPowerLevel_ = 1;
		curPowerRate_ = MAX_ELECTRICITIY_RATE;
		curTime_ = 0;
		UIController_->SetTimeRenderer(curTime_);
		curDay_ = GameStaticData::curDay_;
	}

	{
		elecUsageTimer_ = 0.0f;
		isElecCheckOff_ = false;
		timeUsageTimer_ = 0.0f;
		isTimeCheckOff_ = false;
		isLdoorClosed_ = false;
		isLdoorLighted_ = false;
		isRdoorClosed_ = false;
		isRdoorLighted_ = false;
		noElecDeltaTime_ = 0.0f;
		noElecTimerCounter_ = 0;
		playDeadTimer_ = 0.0f;
		deathSceneTimer_ = 0.0f;
		PrevCCTVState_ = LOCATION::MAX;
		foxyDeathTimer_ = 0.0f;
		freddyDeathTimer_ = 0.0f;
		isPirateCoveChecked_ = false;
		isFoxyRunning_ = false;
		isAnomalyOn_ = false;
		anomalyDice_ = 0;
		bonnieDice_ = 0;
		chicaDice_ = 0;
		winDeltaTime_ = 0.0f;
		alphaChangeTime_ = 0.0f;
		isPhoneStop_ = false;
		isLoadingDone_ = false;
		flag1_ = false;
		flag2_ = false;
		flag3_ = false;
		flag4_ = false;
		CCTVMoveDeltaTime_ = 0.0f;
		alphaChangeTime1_ = 2.0f;
		isCCTVFullyTilted_ = false;
		CCTVMoveFlag_ = false;
		subtitleDeltatime_ = 0.0f;
		isFadeIn_ = false;
		firstLoadingDeltatime_ = 0.0f;
		isMuted_ = false;
	}

	{
		mainRenderer_->SetImage("OfficeBasic.png", true);

		jumpScareRenderer_->Off();

		fanRenderer_->SetImage("OfficeFanDefault.png", true);
		fanRenderer_->GetTransform()->SetLocalPosition({ 49.0f, -41.0f, static_cast<float>(RenderOrder::OBJECT1) });
		fanRenderer_->SetChangeAnimation("OfficeFan");
		fanRenderer_->On();

		lDoorRenderer_->SetImage("LdoorStatic.png", true);
		lDoorRenderer_->GetTransform()->SetLocalPosition({ -615.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1) });
		lDoorRenderer_->On();

		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 595.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1) });
		rDoorRenderer_->On();

		rSwitchRenderer_->SetImage("SwitchR_00.png", true);
		rSwitchRenderer_->GetTransform()->SetLocalPosition({ 730.0f, 0.0f, static_cast<float>(RenderOrder::SWITCH) });
		rSwitchRenderer_->On();

		lSwitchRenderer_->SetImage("SwitchL_00.png", true);
		lSwitchRenderer_->GetTransform()->SetLocalPosition({ -760.0f, 0.0f, static_cast<float>(RenderOrder::SWITCH) });
		lSwitchRenderer_->On();

		UIController_->dayPassHiderUpper_->Off();
		UIController_->dayPassHiderBottom_->Off();
		UIController_->dayPassNum6_->Off();
		UIController_->dayPassNum5_->Off();
		UIController_->dayPassAM_->Off();

		UIController_->dayPassHiderUpper_->GetTransform()->SetLocalPosition({ -1.0f * UIController_->DAYPASS_X_FLOAT, 100.0f, 0.0f });
		UIController_->dayPassHiderUpper_->SetRenderGroup(static_cast<int>(UIRenderOrder::DAYPASSHIDER));
		UIController_->dayPassHiderUpper_->SetAlpha(1.0f);

		UIController_->dayPassHiderBottom_->GetTransform()->SetLocalPosition({ -1.0f * UIController_->DAYPASS_X_FLOAT, -100.0f, 0.0f });
		UIController_->dayPassHiderBottom_->SetRenderGroup(static_cast<int>(UIRenderOrder::DAYPASSHIDER));
		UIController_->dayPassHiderBottom_->SetAlpha(1.0f);

		UIController_->dayPassNum5_->GetTransform()->SetLocalPosition({ -1.0f * UIController_->DAYPASS_X_FLOAT, 0.0f, 0.0f });
		UIController_->dayPassNum5_->SetRenderGroup(static_cast<int>(UIRenderOrder::DAYPASS));
		
		UIController_->dayPassNum6_->GetTransform()->SetLocalPosition({ -1.0f * UIController_->DAYPASS_X_FLOAT, 100.0f, 0.0f });
		UIController_->dayPassNum6_->SetRenderGroup(static_cast<int>(UIRenderOrder::DAYPASS));
		UIController_->dayPassNum6_->SetAlpha(1.0f);

		UIController_->dayPassAM_->GetTransform()->SetLocalPosition({ UIController_->DAYPASS_X_FLOAT, 0.0f, 0.0f });
		UIController_->dayPassAM_->SetRenderGroup(static_cast<int>(UIRenderOrder::DAYPASS));

		UIController_->SetNightTypo(GameStaticData::curDay_);
		UIController_->On();
	}

	{
		fadeScreen_->Reset();
		fadeScreen_->SetAlpha(1.0f);
		fadeScreen_->SetLoadingRenderer();
		fadeScreen_->OnScreen();
		glitchScreen_->SetWhiteNoiseAlpha(0.3f);
	}

	{
		glitchScreen_->PlayWhiteNoise(false);
		UIController_->CCTVRealRenderer_->Off();
		UIController_->foxyRunningRenderer_->Off();
		UIController_->CCTVAnimationRenderer_->Off();
		fanRenderer_->On();

		aiBonnie_->isPlayerStares_ = true;
		aiChica_->isPlayerStares_ = true;
		aiFoxy_->isPlayerStares_ = false;

		UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
	}

	UIController_->ReloadingUI();
	UIController_->dayPassNum5_->SetAlpha(0.0f);
	UIController_->dayPassAM_->SetAlpha(0.0f);

}


void GameController::CheckTime()
{
	// 실시간 델타타임을 가산해 게임 내 시간을 지나게 합니다.
	// 6시로 마커가 도달 시 게임 승리 판정을 내립니다.
	if (6 == curTime_)
	{
		return;
	}
	else if (6 < curTime_)
	{
		GameEngineDebug::MsgBoxError("시간이 7시 이상임에도 게임이 끝나지 않습니다.");
	}


	timeUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (EACH_HOUR_REAL_DURATION <= timeUsageTimer_)
	{
		// 89초가 지나면 시간 마커에 1시간을 더해줍니다.

		timeUsageTimer_ = 0.0f;
		curTime_ += 1;
		UIController_->SetTimeRenderer(curTime_);
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
	LoopAmbient();
	PlayPhoneGuy();
	AICheck();
	UpdateDebugRender();
	UpdateSubtitle();
	CheckDebugInput();
}


void GameController::UpdateDebugRender()
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_RECT"))  
	{
		isDebugOn_ = !isDebugOn_;
	}

	if (true == isDebugOn_)
	{
		GetLevel()->PushDebugRender(UIController_->CCTVButtonCollision_->GetTransform(), CollisionType::Rect);

		if (false == UIController_->cam1ACollision_->IsUpdate()) // 오피스 모드일 때의 판정박스
		{
			GetLevel()->PushDebugRender(rSwitchDoorCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(lSwitchDoorCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(rSwitchLightCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(lSwitchLightCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(freddyNoseCollison_->GetTransform(), CollisionType::Rect);

			GetLevel()->PushDebugRender(UIController_->mouseLeftCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->mouseRightCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->muteCallCollision_->GetTransform(), CollisionType::Rect);
		}
		else if (true == UIController_->cam1ACollision_->IsUpdate())
		{
			GetLevel()->PushDebugRender(UIController_->cam1ACollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam1BCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam1CCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam5Collision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam3Collision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam2ACollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam2BCollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam7Collision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam6Collision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam4ACollision_->GetTransform(), CollisionType::Rect);
			GetLevel()->PushDebugRender(UIController_->cam4BCollision_->GetTransform(), CollisionType::Rect);
		}
	}

}

void GameController::CheckDebugInput()
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIPHOUR") && curTime_ <= 5)
	{
		timeUsageTimer_ = 0.0f;
		curTime_ += 1;
		UIController_->SetTimeRenderer(curTime_);
	}
	if (true == GameEngineInput::GetInst().Press("DEBUG_SKIPELEC") && curPowerRate_ >= 1)
	{
		elecUsageTimer_ = 0.0f;
		curPowerRate_ -= 1.0f;
		UIController_->SetPowerRateRenderer(curPowerRate_);
	}
	if (true == GameEngineInput::GetInst().Down("Foxy"))
	{
		//aiFoxy_->ActivateJumpscare();
		aiFoxy_->ActivateAction();
	}
	if (true == GameEngineInput::GetInst().Down("Chica"))
	{
		//aiChica_->ActivateJumpscare();
		aiChica_->ActivateAction();
	}
	if (true == GameEngineInput::GetInst().Down("Bonnie"))
	{
		//aiBonnie_->ActivateJumpscare();
		aiBonnie_->ActivateAction();
	}
	if (true == GameEngineInput::GetInst().Down("Freddy"))
	{
		//aiFreddy_->ActivateJumpscare();
		aiFreddy_->ActivateAction();
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
	if (false == isLoadingDone_)
	{
		firstLoadingDeltatime_ += GameEngineTime::GetInst().GetDeltaTime();

		if (1.0f <= firstLoadingDeltatime_)
		{
			fadeScreen_->SetAlpha(0.0f);
			firstLoadingDeltatime_ = 0.0f;
			fadeScreen_->RemoveLoadingRenderer();
			isLoadingDone_ = true;
		}
	}

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
		freddyDeathTimer_ += GameEngineTime::GetInst().GetDeltaTime();
		
		if (3.0f <= freddyDeathTimer_)
		{
			return "FreddyDeath";
		}

	}

	if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel())
	{
		if (true == isPirateCoveChecked_)
		{
			foxyDeathTimer_ += GameEngineTime::GetInst().GetDeltaTime();
			foxySound_.PlayAlone("FoxyRun.wav");
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
					foxySound_.PlayOverLap("FoxyDoor.wav");
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

			foxySound_.PlayAlone("FoxyRun.wav");
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
					foxySound_.PlayOverLap("FoxyDoor.wav");
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
			bonnieSound_.PlayAlone("WindowScare.wav");
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
			chicaSound_.PlayAlone("WindowScare.wav");
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
	UIController_->muteCallCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMuteCall, this, std::placeholders::_1));
	UIController_->mouseLeftCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseLeft, this, std::placeholders::_1));
	UIController_->mouseRightCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseRight, this, std::placeholders::_1));
	lSwitchDoorCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionSwitchDoorL, this, std::placeholders::_1));
	lSwitchLightCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionSwitchLightL, this, std::placeholders::_1));
	rSwitchDoorCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionSwitchDoorR, this, std::placeholders::_1));
	rSwitchLightCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionSwitchLightR, this, std::placeholders::_1));
	freddyNoseCollison_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionFreddyNose, this, std::placeholders::_1));


	return StateInfo();
}

StateInfo GameController::startCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션에 앞서 렌더 오더를 새로 정리합니다.
	curPowerLevel_ += 1;
	UIController_->CCTVAnimationRenderer_->On();
	UIController_->CCTVAnimationRenderer_->SetChangeAnimation("CCTVOpen", true);
	return StateInfo();
}

StateInfo GameController::updateCCTVOpen(StateInfo _state)
{
	// CCTV 작동 애니메이션을 여기서 작동 시킵니다.
	// 작동의 짧은 시간동안은 어떤 인풋도 먹히지 않도록 조정합니다.

	if (true == UIController_->CCTVAnimationRenderer_->IsCurAnimationEnd())
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
	UIController_->CCTVRealRenderer_->On();
	UIController_->CCTVAnimationRenderer_->Off();
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
	if (curTime_ == 6)
	{
		return "Win";
	}

	{
		CCTVPlayer_.PlayAlone("CCTV.wav", -1);
	}

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
		switch (randomGenerator_.RandomInt(0,3))
		{
		case 0:
			chicaSound_.PlayAlone("ChicaVoice0.wav");
			break;
		case 1:
			chicaSound_.PlayAlone("ChicaVoice1.wav");
			break;
		case 2:
			chicaSound_.PlayAlone("ChicaVoice2.wav");
			break;
		case 3:
			chicaSound_.PlayAlone("ChicaVoice3.wav");
			break;
		default:
			break;
		}

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

	// 내가 시점을 고정한 곳 CurCCTVState_ 에 보니, 치카, 프레디 중 한 명이 있었는데, 그 시점에 자리를 옮겼다면,
	// 일정 시간동안 CCTV가 먹통이 되는 걸 구현해야 한다.


	if (true == isCCTVGlitched_)
	{
		CCTVGlitchDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();
		UIController_->CCTVRealRenderer_->SetImage("ClearScreen.png", true);
		if (DEFAULT_CCTV_GLITCH_TIME <= CCTVGlitchDeltaTime_)
		{
			CCTVGlitchDeltaTime_ = 0.0f;
			isCCTVGlitched_ = false;
		}
	}
	else
	{
		CheckRecentMovement();
		switch (CurCCTVState_)
		{
			// 현 CCTV가 어디를 지향했는지에 따라
			// 화면을 바꿔 보여줍니다.


		case LOCATION::SHOWSTAGE:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();



			if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation() && LOCATION::SHOWSTAGE != aiFreddy_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("ShowStage_AllGone.png", true);
				break;
			}

			if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation() && LOCATION::SHOWSTAGE == aiFreddy_->GetLocation())
			{
				if (true == isAnomalyOn_)
				{
					UIController_->CCTVRealRenderer_->SetImage("ShowStage_BCGone_Anomaly.png", true);
					if (false == aiFreddy_->isBonnieChica0ut_)
					{
						aiFreddy_->isBonnieChica0ut_ = true;
					}

					break;
				}

				UIController_->CCTVRealRenderer_->SetImage("ShowStage_BCGone.png", true);
				if (false == aiFreddy_->isBonnieChica0ut_)
				{
					aiFreddy_->isBonnieChica0ut_ = true;
				}
				break;
			}
			else if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE == aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("ShowStage_BonnieGone.png", true);
				break;
			}
			else if (LOCATION::SHOWSTAGE == aiBonnie_->GetLocation() && LOCATION::SHOWSTAGE != aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("ShowStage_ChicaGone.png", true);
				break;
			}

			if (true == isAnomalyOn_)
			{
				UIController_->CCTVRealRenderer_->SetImage("ShowStage_Default_Anomaly.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("ShowStage_Default.png", true);
		}
		break;
		case LOCATION::KITCHEN:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			UIController_->CCTVRealRenderer_->SetImage("Kitchen.png", true);
		}
		break;
		case LOCATION::BACKSTAGE:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::BACKSTAGE == aiBonnie_->GetLocation())
			{
				switch (bonnieDice_)
				{
				case 0:
					UIController_->CCTVRealRenderer_->SetImage("BackStage_Bonnie0.png", true);
					break;
				case 1:
					UIController_->CCTVRealRenderer_->SetImage("BackStage_Bonnie1.png", true);
					break;
				default:
					break;
				}
				break;
			}

			if (true == isAnomalyOn_)
			{
				UIController_->CCTVRealRenderer_->SetImage("BackStage_Anomaly.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("BackStage_Default.png", true);
		}
		break;
		case LOCATION::DININGAREA:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::DININGAREA == aiBonnie_->GetLocation() && LOCATION::DININGAREA == aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("DiningArea_Chica1.png", true);
				break;
			}
			else if (LOCATION::DININGAREA == aiBonnie_->GetLocation() && LOCATION::DININGAREA != aiChica_->GetLocation())
			{
				switch (bonnieDice_)
				{
				case 0:
					UIController_->CCTVRealRenderer_->SetImage("DiningArea_Bonnie0.png", true);
					break;
				case 1:
					UIController_->CCTVRealRenderer_->SetImage("DiningArea_Bonnie1.png", true);
					break;
				default:
					break;
				}
				break;
			}
			else if (LOCATION::DININGAREA != aiBonnie_->GetLocation() && LOCATION::DININGAREA == aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("DiningArea_Chica0.png", true);
				break;
			}
			else if (LOCATION::DININGAREA == aiFreddy_->GetLocation() && LOCATION::DININGAREA != aiBonnie_->GetLocation() && LOCATION::DININGAREA != aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("DiningArea_Freddy.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("DiningArea_Default.png", true);
		}
		break;
		case LOCATION::PIRATECOVE:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			FOXYLEVEL curFoxyLevel = aiFoxy_->GetFoxyLevel();

			switch (curFoxyLevel)
			{
			case FOXYLEVEL::LV1:
				UIController_->CCTVRealRenderer_->SetImage("PirateCove_Lv1.png", true);
				break;
			case FOXYLEVEL::LV2:
				UIController_->CCTVRealRenderer_->SetImage("PirateCove_Lv2.png", true);
				break;
			case FOXYLEVEL::LV3:
				UIController_->CCTVRealRenderer_->SetImage("PirateCove_Lv3.png", true);
				break;
			case FOXYLEVEL::LV4:
			{
				//isPirateCoveChecked_ = true;
				if (true == randomGenerator_.RandomBool(5.0f / 100.0f))
				{
					UIController_->CCTVRealRenderer_->SetImage("PirateCove_Lv4_Anomaly.png", true);
				}
				UIController_->CCTVRealRenderer_->SetImage("PirateCove_Lv4.png", true);
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
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::EASTHALLA == aiChica_->GetLocation())
			{
				switch (chicaDice_)
				{
				case 0:
					UIController_->CCTVRealRenderer_->SetImage("EastHallA_Chica0.png", true);
					break;
				case 1:
					UIController_->CCTVRealRenderer_->SetImage("EastHallA_Chica1.png", true);
					break;
				default:
					break;
				}
				break;
			}
			else if (LOCATION::EASTHALLA != aiChica_->GetLocation() && LOCATION::EASTHALLA == aiFreddy_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("EastHallA_Freddy.png", true);
				break;
			}

			if (true == isAnomalyOn_)
			{
				switch (anomalyDice_)
				{
				case 0:
				case 1:
					UIController_->CCTVRealRenderer_->SetImage("EastHallA_Anomaly0.png", true);
					break;
				case 2:
				case 3:
					UIController_->CCTVRealRenderer_->SetImage("EastHallA_Anomaly1.png", true);
					break;

				default:
					break;
				}
				break;
			}
			UIController_->CCTVRealRenderer_->SetImage("EastHallA_Default.png", true);
		}
		break;

		case LOCATION::EASTHALLB:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::EASTHALLB == aiFreddy_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("EastHallB_Freddy.png", true);
				break;
			}
			else if (LOCATION::EASTHALLB == aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("EastHallB_Chica0.png", true);
				break;
			}


			if (true == isAnomalyOn_)
			{
				switch (anomalyDice_)
				{
				case 0:
					UIController_->CCTVRealRenderer_->SetImage("EastHallB_Anomaly0.png", true);
					break;
				case 1:
					UIController_->CCTVRealRenderer_->SetImage("EastHallB_Anomaly1.png", true);
					break;
				case 2:
					UIController_->CCTVRealRenderer_->SetImage("EastHallB_Anomaly2.png", true);
break;
				case 3:
					UIController_->CCTVRealRenderer_->SetImage("EastHallB_Anomaly3.png", true);
					break;
				default:
					break;
				}
				break;
			}
			UIController_->CCTVRealRenderer_->SetImage("EastHallB_Default.png", true);
		}
		break;
		case LOCATION::WESTHALLA:
		{
			if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel() && false == isFoxyRunning_)
			{
				isFoxyRunning_ = true;
				UIController_->foxyRunningRenderer_->On();
				awakePlayer_.PlayAlone("FoxyRun.wav");
				UIController_->foxyRunningRenderer_->SetChangeAnimation("RunningFoxy", true);
				UIController_->CCTVRealRenderer_->Off();
				break;
			}
			else if (FOXYLEVEL::LV4 == aiFoxy_->GetFoxyLevel() && true == isFoxyRunning_)
			{
				break;
			}

			UIController_->CCTVRealRenderer_->On();
			UIController_->foxyRunningRenderer_->Off();

			if (LOCATION::WESTHALLA == aiBonnie_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("WestHallA_Bonnie.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("WestHallA_Default.png", true);

		}
		break;
		case LOCATION::WESTHALLB:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::WESTHALLB == aiBonnie_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("WestHallB_Bonnie0.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("WestHallB_Default.png", true);
		}
		break;
		case LOCATION::RESTROOMS:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::RESTROOMS == aiChica_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("RestRooms_Chica0.png", true);
				break;
			}
			else if (LOCATION::RESTROOMS == aiFreddy_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("RestRooms_Freddy.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("RestRooms_Default.png", true);
		}
		break;
		case LOCATION::SUPPLYCLOSET:
		{
			UIController_->foxyRunningRenderer_->Off();
			UIController_->CCTVRealRenderer_->On();

			if (LOCATION::SUPPLYCLOSET == aiBonnie_->GetLocation())
			{
				UIController_->CCTVRealRenderer_->SetImage("SuppltCloset_Bonnie.png", true);
				break;
			}

			UIController_->CCTVRealRenderer_->SetImage("SupplyCloset_Default.png", true);
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


		CCTVScreenMove();
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
		UIController_->CCTVRealRenderer_->Off();
		UIController_->foxyRunningRenderer_->On();
		UIController_->foxyRunningRenderer_->SetChangeAnimation("RunningFoxy", true);
	}
	if (true == GameEngineInput::GetInst().Down("ESC"))
	{
		UIController_->foxyRunningRenderer_->Off();
		UIController_->CCTVRealRenderer_->On();
	}


	return StateInfo();
}


StateInfo GameController::startCCTVClose(StateInfo _state)
{
	CCTVPlayer_.Stop();
	glitchScreen_->PlayWhiteNoise(false);
	curPowerLevel_ -= 1;
	UIController_->CCTVRealRenderer_->Off();
	UIController_->foxyRunningRenderer_->Off();
	UIController_->CCTVAnimationRenderer_->On();
	if (curPowerRate_ != 0.0f)
	{
		fanRenderer_->On();
	}

	aiBonnie_->isPlayerStares_ = true;
	aiChica_->isPlayerStares_ = true;
	aiFoxy_->isPlayerStares_ = false;

	UIController_->CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	return StateInfo();
}

StateInfo GameController::updateCCTVClose(StateInfo _state)
{
	if (true == UIController_->CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		if (curPowerRate_ != 0)
		{
			mainRenderer_->SetImage("OfficeBasic.png", true);
		}

		UIController_->CCTVAnimationRenderer_->Off();

		return "Idle";
	}
	return StateInfo();
}

StateInfo GameController::startBonnieDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	UIController_->CCTVRealRenderer_->Off();
	UIController_->CCTVAnimationRenderer_->On();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	UIController_->CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	
	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("JumpScareBonnie", true);
	//mainRenderer_->SetChangeAnimation("JumpScareBonnie", true);
	isElecCheckOff_ = true;
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	lSwitchRenderer_->Off();
	rSwitchRenderer_->Off();

	awakePlayer_.PlayOverLap("JumpScare.wav");

	GetTransform()->SetLocalPosition({0.0f, 0.0f, 0.0f});
	return StateInfo();
}

StateInfo GameController::updateBonnieDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (true == UIController_->CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		UIController_->CCTVAnimationRenderer_->Off();
	}

	if (0.88f <= deathSceneTimer_)
	{
		StopAllSound();
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startChicaDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	isElecCheckOff_ = true;
	UIController_->CCTVRealRenderer_->Off();
	UIController_->CCTVAnimationRenderer_->On();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	UIController_->CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("JumpScareChica", true);
	//mainRenderer_->SetChangeAnimation("JumpScareChica", true);
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	lSwitchRenderer_->Off();
	rSwitchRenderer_->Off();

	awakePlayer_.PlayOverLap("JumpScare.wav");

	GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	return StateInfo();
}

StateInfo GameController::updateChicaDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (true == UIController_->CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		UIController_->CCTVAnimationRenderer_->Off();
	}

	if (0.88f <= deathSceneTimer_)
	{
		StopAllSound();
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startFoxyDeath(StateInfo _state)
{
	isFoxyRunning_ = false;
	isElecCheckOff_ = true;
	glitchScreen_->PlayWhiteNoise(false);
	UIController_->CCTVRealRenderer_->Off();
	UIController_->CCTVAnimationRenderer_->Off();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });
	
	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("JumpScareFoxy", true);

	lDoorRenderer_->Off();
	rDoorRenderer_->Off();

	awakePlayer_.PlayOverLap("JumpScare.wav");
	return StateInfo();
}

StateInfo GameController::updateFoxyDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (0.88f <= deathSceneTimer_)
	{
		StopAllSound();
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}

StateInfo GameController::startFreddyDeath(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	isElecCheckOff_ = true;
	UIController_->CCTVRealRenderer_->Off();
	UIController_->CCTVAnimationRenderer_->Off();
	fanRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,100.0f });

	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("JumpScareFreddy", true);
	//mainRenderer_->SetChangeAnimation("JumpScareFreddy", true);
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	lSwitchRenderer_->Off();
	rSwitchRenderer_->Off();
	awakePlayer_.PlayOverLap("JumpScare.wav");
	return StateInfo();
}

StateInfo GameController::updateFreddyDeath(StateInfo _state)
{
	deathSceneTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (0.88f <= deathSceneTimer_)
	{
		StopAllSound();
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}


StateInfo GameController::startNoElec(StateInfo _state)
{
	glitchScreen_->PlayWhiteNoise(false);
	ambientPlayer_.Stop();
	CCTVPlayer_.Stop();
	phoneGuyPlayer_.Stop();
	awakePlayer_.Stop();
	rlightSound_.Stop();
	llightSound_.Stop();
	bonnieSound_.Stop();
	chicaSound_.Stop();
	freddySound_.Stop();
	foxySound_.Stop();
	ambientPlayer_.PlayAlone("PowerDown.wav");

	UIController_->Off();

	if (CurPlayerState_ != PLAYERSTATUS::OFFICE)
	{
		UIController_->CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
		UIController_->CCTVRealRenderer_->Off();
	}
	
	isElecCheckOff_ = true;
	elecUsageTimer_ = 0.0f;

	mainRenderer_->SetImage("NoElecStatic.png", true);
	fanRenderer_->Off();

	if (true == isRdoorClosed_)
	{
		awakePlayer_.PlayOverLap("Door.wav");
		rDoorRenderer_->SetChangeAnimation("RdoorOpen");
		isRdoorClosed_ = false;
	}

	if (true == isLdoorClosed_)
	{
		awakePlayer_.PlayOverLap("Door.wav");
		lDoorRenderer_->SetChangeAnimation("LdoorOpen");
		isLdoorClosed_ = false;
	}

	{
		lSwitchRenderer_->Off();
		rSwitchRenderer_->Off();
	}

	return StateInfo();
}

StateInfo GameController::updateNoElec(StateInfo _state)
{

// 5초마다 1 / 5 확률로(최대 20초) 노래가 멈추고 화면이 암전된다
// 이후 2초마다 1 / 5 확률로 프레디가 점프스케어

	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (true == rDoorRenderer_->IsCurAnimationEnd())
	{
		rDoorRenderer_->Off();
	}
	if (true == lDoorRenderer_->IsCurAnimationEnd())
	{
		lDoorRenderer_->Off();
	}


	if (4 == noElecTimerCounter_)
	{
		ambientPlayer_.Stop();
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
			ambientPlayer_.Stop();
			return "HeisComing";
		}
		break;
		default:
			break;
		}
	}

	{
		UIController_->mouseLeftCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseLeft, this, std::placeholders::_1));
		UIController_->mouseRightCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseRight, this, std::placeholders::_1));
	}

	return StateInfo();
}


StateInfo GameController::startHeisComing(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	
	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("NoElec", true);
	//mainRenderer_->SetChangeAnimation("NoElec");

	ambientPlayer_.PlayAlone("MusicBox.wav");
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

	{
		UIController_->mouseLeftCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseLeft, this, std::placeholders::_1));
		UIController_->mouseRightCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionMouseRight, this, std::placeholders::_1));
	}

	return StateInfo();
}

StateInfo GameController::startHeKillsYou(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;

	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("NoElecBlink", true);

	ambientPlayer_.Stop();
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
	jumpScareRenderer_->On();
	jumpScareRenderer_->SetChangeAnimation("NoElecFreddy", true);
	awakePlayer_.PlayOverLap("JumpScare.wav");
	return StateInfo();
}

StateInfo GameController::updateNoElecDeath(StateInfo _state)
{
	if (true == jumpScareRenderer_->IsCurAnimationEnd())
	{
		awakePlayer_.Stop();
		GetLevel()->RequestLevelChange("GameOver");
	}

	return StateInfo();
}


StateInfo GameController::startWin(StateInfo _state)
{
	isElecCheckOff_ = true;
	StopAllSound();
	fadeScreen_->OnScreen();

	isMuted_ = true;
	UIController_->dayPassNum5_->On();
	UIController_->dayPassAM_->On();

	alphaChangeTime_ = 0.0f;
	winDeltaTime_ = 0.0f;

	{
		aiBonnie_->Off();
		aiChica_->Off();
		aiFoxy_->Off();
		aiFreddy_->Off();
	}

	ambientPlayer_.PlayAlone("WinChime.wav");

	return StateInfo();
}

StateInfo GameController::updateWin(StateInfo _state)
{
	winDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	glitchScreen_->SetStatic();

	if (0.5f <= winDeltaTime_ && false == fadeScreen_->isFullDark_)
	{
		if (false == isFadeIn_)
		{
			fadeScreen_->StartDark(1.5f);

			isFadeIn_ = true;
		}
		UpdateAlphaChange();
	}

	if (true == fadeScreen_->isFullDark_)
	{
		UIController_->dayPassHiderUpper_->On();
		UIController_->dayPassHiderBottom_->On();
		UIController_->dayPassNum6_->On();

	}

	if (2.5f <= winDeltaTime_)
	{
		if (UIController_->dayPassNum6_->GetTransform()->GetLocalPosition().y >= UIController_->dayPassAM_->GetTransform()->GetLocalPosition().y)
		{
			UIController_->dayPassNum6_->GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 30.0f);
			UIController_->dayPassNum5_->GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 30.0f);
		}
		else if (8.0f <= winDeltaTime_)
		{
			if (0.0f <= alphaChangeTime1_)
			{
				awakePlayer_.PlayAlone("WinChildren.wav");
				alphaChangeTime1_ -= GameEngineTime::GetInst().GetDeltaTime();

				UIController_->dayPassAM_->SetAlpha(alphaChangeTime1_/2.0f);
				UIController_->dayPassNum6_->SetAlpha(alphaChangeTime1_/2.0f);
			}
		}
	}

	if (10.0f <= winDeltaTime_)
	{
		switch (GameStaticData::curDay_)
		{
		case DAY::DAY1:
			GameStaticData::curDay_ = DAY::DAY2;
			GameStaticData::savedDay_ = GameStaticData::curDay_;
			StopAllSound();
			GetLevel()->RequestLevelChange("Intermission");
			break;
		case DAY::DAY2:
			GameStaticData::curDay_ = DAY::DAY3;
			GameStaticData::savedDay_ = GameStaticData::curDay_;
			StopAllSound();
			GetLevel()->RequestLevelChange("Intermission");
			break;
		case DAY::DAY3:
			GameStaticData::curDay_ = DAY::DAY4;
			GameStaticData::savedDay_ = GameStaticData::curDay_;
			StopAllSound();
			GetLevel()->RequestLevelChange("Intermission");
			break;
		case DAY::DAY4:
			GameStaticData::curDay_ = DAY::DAY5;
			GameStaticData::savedDay_ = GameStaticData::curDay_;
			StopAllSound();
			GetLevel()->RequestLevelChange("Intermission");
			break;
		case DAY::DAY5:
			GameStaticData::savedDay_ = GameStaticData::curDay_;
			StopAllSound();
			GetLevel()->RequestLevelChange("TrialOver");
			break;
		case DAY::DAY6:
			StopAllSound();
			GetLevel()->RequestLevelChange("TrialOver");
			break;
		case DAY::CUSTOM:
			StopAllSound();
			GetLevel()->RequestLevelChange("TrialOver");
			break;
		default:
			break;
		}
	}

	return StateInfo();
}

void GameController::UpdateAlphaChange()
{
	if (1.5f >= alphaChangeTime_)
	{
		alphaChangeTime_ += GameEngineTime::GetInst().GetDeltaTime();

		UIController_->dayPassNum5_->SetAlpha(alphaChangeTime_/1.5f);
		UIController_->dayPassAM_->SetAlpha(alphaChangeTime_/1.5f);
	}
}



void GameController::CollisionSwitchDoorL(GameEngineCollision* _other)
{
	if (PLAYERSTATUS::OFFICE != CurPlayerState_)
	{
		return;
	}

	if (true == GameEngineInput::GetInst().Down("MOUSE_1") && true == lDoorRenderer_->IsCurAnimationEnd())
	{
		awakePlayer_.PlayOverLap("Door.wav");
		if (false == isLdoorClosed_)
		{
			if (true == isLdoorLighted_)
			{
				lSwitchRenderer_->SetImage("SwitchL_11.png", true);
			}
			else
			{
				lSwitchRenderer_->SetImage("SwitchL_10.png", true);
			}
			
			isLdoorClosed_ = true;
			aiBonnie_->isDoorLocked_ = true;
			aiFoxy_->isDoorLocked_ = true;
			curPowerLevel_ += 1;
		}
		else
		{
			if (true == isLdoorLighted_)
			{
				lSwitchRenderer_->SetImage("SwitchL_01.png", true);
			}
			else
			{
				lSwitchRenderer_->SetImage("SwitchL_00.png", true);
			}

			isLdoorClosed_ = false;
			aiBonnie_->isDoorLocked_ = false;
			aiFoxy_->isDoorLocked_ = false;
			curPowerLevel_ -= 1;
		}
	}
}

void GameController::CollisionSwitchDoorR(GameEngineCollision* _other)
{
	if (PLAYERSTATUS::OFFICE != CurPlayerState_)
	{
		return;
	}

	if (true == GameEngineInput::GetInst().Down("MOUSE_1") && true == rDoorRenderer_->IsCurAnimationEnd())
	{
		doorSound_.PlayOverLap("Door.wav");
		if (false == isRdoorClosed_)
		{
			if (true == isRdoorLighted_)
			{
				rSwitchRenderer_->SetImage("SwitchR_11.png", true);
			}
			else
			{
				rSwitchRenderer_->SetImage("SwitchR_10.png", true);
			}

			isRdoorClosed_ = true;
			aiChica_->isDoorLocked_ = true;
			aiFreddy_->isDoorLocked_ = true;
			curPowerLevel_ += 1;

		}
		else
		{
			if (true == isRdoorLighted_)
			{
				rSwitchRenderer_->SetImage("SwitchR_01.png", true);
			}
			else
			{
				rSwitchRenderer_->SetImage("SwitchR_00.png", true);
			}

			isRdoorClosed_ = false;
			aiChica_->isDoorLocked_ = false;
			aiFreddy_->isDoorLocked_ = false;
			curPowerLevel_ -= 1;
		}
	}
}

void GameController::CollisionSwitchLightL(GameEngineCollision* _other)
{
	if (PLAYERSTATUS::OFFICE != CurPlayerState_)
	{
		return;
	}

	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		if (false == isLdoorLighted_) // 켜져있지 않은 경우
		{
			if (true == isRdoorLighted_)
			{
				if (true == isRdoorClosed_)
				{
					rSwitchRenderer_->SetImage("SwitchR_10.png", true);
				}
				else
				{
					rSwitchRenderer_->SetImage("SwitchR_00.png", true);
				}

				rlightSound_.Stop();
				isRdoorLighted_ = false;
				curPowerLevel_--;
			}

			if (true == isLdoorClosed_)
			{
				lSwitchRenderer_->SetImage("SwitchL_11.png", true);
			}
			else
			{
				lSwitchRenderer_->SetImage("SwitchL_01.png", true);
			}

			llightSound_.PlayOverLap("DoorLight.wav", -1);
			isLdoorLighted_ = true;


			curPowerLevel_++;

		}
		else // 이미 켜져있는 경우
		{
			if (true == isLdoorClosed_)
			{
				lSwitchRenderer_->SetImage("SwitchL_10.png", true);
			}
			else
			{
				lSwitchRenderer_->SetImage("SwitchL_00.png", true);
			}

			llightSound_.Stop();
			isLdoorLighted_ = false;
			curPowerLevel_ -= 1;
		}
	}
}

void GameController::CollisionSwitchLightR(GameEngineCollision* _other)
{
	if (PLAYERSTATUS::OFFICE != CurPlayerState_)
	{
		return;
	}

	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		if (false == isRdoorLighted_)
		{
			if (true == isLdoorLighted_)
			{
				if (true == isLdoorClosed_)
				{
					lSwitchRenderer_->SetImage("SwitchL_10.png", true);
				}
				else
				{
					lSwitchRenderer_->SetImage("SwitchL_00.png", true);
				}


				llightSound_.Stop();
				isLdoorLighted_ = false;
				curPowerLevel_--;
			}

			if (true == isRdoorClosed_)
			{
				rSwitchRenderer_->SetImage("SwitchR_11.png", true);
			}
			else
			{
				rSwitchRenderer_->SetImage("SwitchR_01.png", true);
			}

			rlightSound_.PlayOverLap("DoorLight.wav", -1);
			isRdoorLighted_ = true;

			curPowerLevel_ += 1;

		}
		else
		{
			if (true == isRdoorClosed_)
			{
				rSwitchRenderer_->SetImage("SwitchR_10.png", true);
			}
			else
			{
				rSwitchRenderer_->SetImage("SwitchR_00.png", true);
			}
			rlightSound_.Stop();
			isRdoorLighted_ = false;
			curPowerLevel_ -= 1;
		}
	}
}


void GameController::CollisionFreddyNose(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("FreddyNose.wav");
	}
}



void GameController::CollisionCCTVButton(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVOnOff.wav");
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
	if (true == GameEngineInput::GetInst().Down("MOUSE_1") && false == isMuted_)
	{
		UIController_->muteCallRenderer_->Off();
		UIController_->muteCallCollision_->Off();
		phoneGuyPlayer_.Stop();
		isMuted_ = true;
	}
}

void GameController::CollisionCam1A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::SHOWSTAGE;
	}
}

void GameController::CollisionCam1B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::DININGAREA;
	}
}

void GameController::CollisionCam1C(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::PIRATECOVE;
	}
}

void GameController::CollisionCam3(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::SUPPLYCLOSET;
	}
}

void GameController::CollisionCam5(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::BACKSTAGE;
	}
}

void GameController::CollisionCam2A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::WESTHALLA;
	}
}

void GameController::CollisionCam2B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::WESTHALLB;
	}
}

void GameController::CollisionCam7(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::RESTROOMS;
	}
}

void GameController::CollisionCam6(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::KITCHEN;
	}
}

void GameController::CollisionCam4A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::EASTHALLA;
	}
}
void GameController::CollisionCam4B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		glitchScreen_->PlayAwakeScanLineFast();
		PrevCCTVState_ = CurCCTVState_;
		CurCCTVState_ = LOCATION::EASTHALLB;
	}
}


void GameController::CollisionMouseLeft(GameEngineCollision* _other)
{
	if (152.0f >= GetTransform()->GetWorldPosition().x)
	{
		GetTransform()->SetWorldDeltaTimeMove(float4::RIGHT * DEFAULT_MOUSE_SCROLLSPEED);
	}
}

void GameController::CollisionMouseRight(GameEngineCollision* _other)
{
	if (-152.0f <= GetTransform()->GetWorldPosition().x)
	{
		GetTransform()->SetWorldDeltaTimeMove(float4::LEFT * DEFAULT_MOUSE_SCROLLSPEED);
	}
}

void GameController::LoopAmbient()
{
	if (0.0f >= fadeScreen_->GetReleaseTime() && false == isElecCheckOff_ && true == isLoadingDone_)
	{
		ambientPlayer_.GetChannel()->setVolume(0.2f);
		ambientPlayer_.PlayAlone("Office.wav", -1);
	}
}

void GameController::PlayPhoneGuy()
{
	if (false == isElecCheckOff_ && false == isPhoneStop_)
	{
		switch (curDay_)
		{
		case DAY::DAY1:
			phoneGuyPlayer_.PlayAlone("Phone1.wav");
			break;
		case DAY::DAY2:
			phoneGuyPlayer_.PlayAlone("Phone2.wav");
			break;
		case DAY::DAY3:
			phoneGuyPlayer_.PlayAlone("Phone3.wav");
			break;
		case DAY::DAY4:
			phoneGuyPlayer_.PlayAlone("Phone4.wav");
			break;
		case DAY::DAY5:
			phoneGuyPlayer_.PlayAlone("Phone5.wav");
			break;
		case DAY::DAY6:
			phoneGuyPlayer_.PlayAlone("Phone6.wav");
			break;
		case DAY::CUSTOM:
			break;
		case DAY::MAX:
			break;
		default:
			break;
		}

		isPhoneStop_ = true;
	}
	

}


void GameController::CheckRecentMovement()
{
	if (true == aiBonnie_->isRecentlyMoved_ )
	{
		if (CurCCTVState_ == aiBonnie_->GetPrevLocation() || CurCCTVState_ == aiBonnie_->GetLocation())
		{
			glitchScreen_->PlayAwakeScanLineFast();
			awakePlayer_.PlayOverLap("CCTVError0.wav");
			isCCTVGlitched_ = true;
			aiBonnie_->isRecentlyMoved_ = false;
			return;
		}
		else
		{
			aiBonnie_->isRecentlyMoved_ = false;
		}
	}

	if (true == aiChica_->isRecentlyMoved_)
	{
		if (CurCCTVState_ == aiChica_->GetPrevLocation() || CurCCTVState_ == aiChica_->GetLocation())
		{
			glitchScreen_->PlayAwakeScanLineFast();
			awakePlayer_.PlayOverLap("CCTVError0.wav");
			isCCTVGlitched_ = true;
			aiChica_->isRecentlyMoved_ = false;
			return;
		}
		else
		{
			aiChica_->isRecentlyMoved_ = false;
		}
	}
	
	if (true == aiFreddy_->isRecentlyMoved_)
	{
		if (CurCCTVState_ == aiFreddy_->GetPrevLocation() || CurCCTVState_ == aiFreddy_->GetLocation())
		{
			glitchScreen_->PlayAwakeScanLineFast();
			awakePlayer_.PlayOverLap("CCTVError0.wav");
			isCCTVGlitched_ = true;
			aiFreddy_->isRecentlyMoved_ = false;
			return;
		}
		else
		{
			aiFreddy_->isRecentlyMoved_ = false;
		}
	}
}

void GameController::StopAllSound()
{
	ambientPlayer_.Stop();
	CCTVPlayer_.Stop();
	awakePlayer_.Stop();
	phoneGuyPlayer_.Stop();
	doorSound_.Stop();
	rlightSound_.Stop();
	llightSound_.Stop();
	bonnieSound_.Stop();
	chicaSound_.Stop();
	freddySound_.Stop();
	foxySound_.Stop();
}

void GameController::CCTVScreenMove()
{
	if (true == isCCTVFullyTilted_)
	{
		CCTVMoveDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

		if (1.5f <= CCTVMoveDeltaTime_)
		{

			if (true == CCTVMoveFlag_)
			{
				CCTVMoveFlag_ = false;
			}
			else 
			{
				CCTVMoveFlag_ = true;
			}

			isCCTVFullyTilted_ = false;
			CCTVMoveDeltaTime_ = 0.0f;
		}
	}
	else
	{
		if (false == CCTVMoveFlag_) // 좌로
		{
			if (-150.0f <= UIController_->CCTVRealRenderer_->GetTransform()->GetLocalPosition().x)
			{
				UIController_->CCTVRealRenderer_->GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * DEFAULT_CCTV_SCREEN_MOVESPEED);
			}
			else
			{
				isCCTVFullyTilted_ = true;
			}
		}
		else if (true == CCTVMoveFlag_) // 우로
		{
			if (150.0f >= UIController_->CCTVRealRenderer_->GetTransform()->GetLocalPosition().x)
			{
				UIController_->CCTVRealRenderer_->GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * DEFAULT_CCTV_SCREEN_MOVESPEED);
			}
			else
			{
				isCCTVFullyTilted_ = true;
			}
		}
	}



}

void GameController::UpdateSubtitle()
{
	if (true == isMuted_)
	{
		UIController_->subtitleRenderer_->Off();
		UIController_->muteCallRenderer_->Off();
		subtitleDeltatime_ = 0.0f;
		subtitleIndex_ = 0;
		return;
	}

	subtitleDeltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	switch (curDay_)
	{
	case DAY::DAY1:
		if (18.0f <= subtitleDeltatime_ && 0 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY1_0001.png", true);
			subtitleIndex_++;
		}

		if (21.0f <= subtitleDeltatime_ && 1 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0002.png", true);
			subtitleIndex_++;
		}

		if (30.0f <= subtitleDeltatime_ && 2 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0003.png", true);
			subtitleIndex_++;
		}

		if (35.0f <= subtitleDeltatime_ && 3 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0004.png", true);
			subtitleIndex_++;
		}

		if (42.0f <= subtitleDeltatime_ && 4 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0005.png", true);
			subtitleIndex_++;
		}

		if (47.0f <= subtitleDeltatime_ && 5 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0006.png", true);
			subtitleIndex_++;
		}

		if (53.0f <= subtitleDeltatime_ && 6 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0007.png", true);
			subtitleIndex_++;
		}

		if (55.0f <= subtitleDeltatime_ && 7 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0008.png", true);
			subtitleIndex_++;
		}

		if (64.0f <= subtitleDeltatime_ && 8 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0009.png", true);
			subtitleIndex_++;
		}

		if (67.0f <= subtitleDeltatime_ && 9 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0010.png", true);
			subtitleIndex_++;
		}

		if (69.0f <= subtitleDeltatime_ && 10 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0011.png", true);
			subtitleIndex_++;
		}

		if (71.0f <= subtitleDeltatime_ && 11 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0012.png", true);
			subtitleIndex_++;
		}

		if (74.0f <= subtitleDeltatime_ && 12 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0013.png", true);
			subtitleIndex_++;
		}

		if (79.0f <= subtitleDeltatime_ && 13 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0014.png", true);
			subtitleIndex_++;
		}

		if (81.0f <= subtitleDeltatime_ && 14 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0015.png", true);
			subtitleIndex_++;
		}

		if (85.0f <= subtitleDeltatime_ && 15 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0016.png", true);
			subtitleIndex_++;
		}

		if (90.0f <= subtitleDeltatime_ && 16 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0017.png", true);
			subtitleIndex_++;
		}

		if (93.0f <= subtitleDeltatime_ && 17 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0018.png", true);
			subtitleIndex_++;
		}

		if (97.0f <= subtitleDeltatime_ && 18 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0019.png", true);
			subtitleIndex_++;
		}

		if (101.0f <= subtitleDeltatime_ && 19 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0020.png", true);
			subtitleIndex_++;
		}

		if (105.0f <= subtitleDeltatime_ && 20 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0021.png", true);
			subtitleIndex_++;
		}

		if (110.0f <= subtitleDeltatime_ && 21 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0022.png", true);
			subtitleIndex_++;
		}

		if (114.0f <= subtitleDeltatime_ && 22 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0023.png", true);
			subtitleIndex_++;
		}

		if (118.0f <= subtitleDeltatime_ && 23 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0024.png", true);
			subtitleIndex_++;
		}

		if (122.0f <= subtitleDeltatime_ && 24 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0025.png", true);
			subtitleIndex_++;
		}

		if (129.0f <= subtitleDeltatime_ && 25 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0026.png", true);
			subtitleIndex_++;
		}

		if (133.0f <= subtitleDeltatime_ && 26 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0027.png", true);
			subtitleIndex_++;
		}

		if (136.0f <= subtitleDeltatime_ && 27 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0028.png", true);
			subtitleIndex_++;
		}

		if (142.0f <= subtitleDeltatime_ && 28 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0029.png", true);
			subtitleIndex_++;
		}

		if (149.0f <= subtitleDeltatime_ && 29 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0030.png", true);
			subtitleIndex_++;
		}

		if (154.0f <= subtitleDeltatime_ && 30 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0031.png", true);
			subtitleIndex_++;
		}

		if (158.0f <= subtitleDeltatime_ && 31 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0032.png", true);
			subtitleIndex_++;
		}

		if (164.0f <= subtitleDeltatime_ && 32 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0033.png", true);
			subtitleIndex_++;
		}

		if (172.0f <= subtitleDeltatime_ && 33 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0034.png", true);
			subtitleIndex_++;
		}

		if (179.0f <= subtitleDeltatime_ && 34 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0035.png", true);
			subtitleIndex_++;
		}

		if (182.0f <= subtitleDeltatime_ && 35 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0036.png", true);
			subtitleIndex_++;
		}

		if (189.0f <= subtitleDeltatime_ && 36 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0037.png", true);
			subtitleIndex_++;
		}

		if (192.0f <= subtitleDeltatime_ && 37 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0038.png", true);
			subtitleIndex_++;
		}

		if (194.0f <= subtitleDeltatime_ && 38 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0039.png", true);
			subtitleIndex_++;
		}

		if (195.0f <= subtitleDeltatime_ && 39 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->SetImage("DAY1_0040.png", true);
			subtitleIndex_++;
		}

		if (200.0f <= subtitleDeltatime_ && 40 == subtitleIndex_)
		{
			isMuted_ = true;
			subtitleDeltatime_ = 0.0f;
			subtitleIndex_ = 0;
		}

		break;

	case DAY::DAY2:

		if (18.0f <= subtitleDeltatime_ && 0 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0001.png", true);
			subtitleIndex_++;
		}

		if (21.0f <= subtitleDeltatime_ && 1 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0002.png", true);
			subtitleIndex_++;
		}

		if (25.0f <= subtitleDeltatime_ && 2 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0003.png", true);
			subtitleIndex_++;
		}

		if (27.0f <= subtitleDeltatime_ && 3 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0004.png", true);
			subtitleIndex_++;
		}

		if (32.0f <= subtitleDeltatime_ && 4 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0005.png", true);
			subtitleIndex_++;
		}

		if (34.0f <= subtitleDeltatime_ && 5 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0006.png", true);
			subtitleIndex_++;
		}

		if (40.0f <= subtitleDeltatime_ && 6 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0007.png", true);
			subtitleIndex_++;
		}

		if (44.0f <= subtitleDeltatime_ && 7 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0008.png", true);
			subtitleIndex_++;
		}

		if (48.0f <= subtitleDeltatime_ && 8 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0009.png", true);
			subtitleIndex_++;
		}

		if (53.0f <= subtitleDeltatime_ && 9 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0010.png", true);
			subtitleIndex_++;
		}

		if (57.0f <= subtitleDeltatime_ && 10 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0011.png", true);
			subtitleIndex_++;
		}

		if (64.0f <= subtitleDeltatime_ && 11 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0012.png", true);
			subtitleIndex_++;
		}

		if (72.0f <= subtitleDeltatime_ && 12 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0013.png", true);
			subtitleIndex_++;
		}

		if (75.0f <= subtitleDeltatime_ && 13 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0014.png", true);
			subtitleIndex_++;
		}

		if (81.0f <= subtitleDeltatime_ && 14 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0015.png", true);
			subtitleIndex_++;
		}

		if (86.0f <= subtitleDeltatime_ && 15 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0016.png", true);
			subtitleIndex_++;
		}

		if (87.8f <= subtitleDeltatime_ && 16 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0017.png", true);
			subtitleIndex_++;
		}

		if (92.0f <= subtitleDeltatime_ && 17 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0018.png", true);
			subtitleIndex_++;
		}

		if (95.8f <= subtitleDeltatime_ && 18 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY2_0019.png", true);
			subtitleIndex_++;
		}

		if (102.0f <= subtitleDeltatime_ && 19 == subtitleIndex_)
		{
			isMuted_ = true;
			subtitleDeltatime_ = 0.0f;
			subtitleIndex_ = 0;
		}

		break;
	case DAY::DAY3:
		
		if (18.0f <= subtitleDeltatime_ && 0 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0001.png", true);
			subtitleIndex_++;
		}

		if (20.0f <= subtitleDeltatime_ && 1 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0002.png", true);
			subtitleIndex_++;
		}

		if (25.0f <= subtitleDeltatime_ && 2 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0003.png", true);
			subtitleIndex_++;
		}

		if (34.0f <= subtitleDeltatime_ && 3 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0004.png", true);
			subtitleIndex_++;
		}

		if (39.7f <= subtitleDeltatime_ && 4 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0005.png", true);
			subtitleIndex_++;
		}

		if (42.5f <= subtitleDeltatime_ && 5 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0006.png", true);
			subtitleIndex_++;
		}

		if (47.5f <= subtitleDeltatime_ && 6 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0007.png", true);
			subtitleIndex_++;
		}

		if (48.7f <= subtitleDeltatime_ && 7 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0008.png", true);
			subtitleIndex_++;
		}

		if (50.5f <= subtitleDeltatime_ && 8 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0009.png", true);
			subtitleIndex_++;
		}

		if (56.0f <= subtitleDeltatime_ && 9 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0010.png", true);
			subtitleIndex_++;
		}

		if (61.0f <= subtitleDeltatime_ && 10 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0011.png", true);
			subtitleIndex_++;
		}

		if (63.5f <= subtitleDeltatime_ && 11 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0012.png", true);
			subtitleIndex_++;
		}

		if (69.0f <= subtitleDeltatime_ && 12 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY3_0013.png", true);
			subtitleIndex_++;
		}

		if (73.0f <= subtitleDeltatime_ && 13 == subtitleIndex_)
		{
			isMuted_ = true;
			subtitleDeltatime_ = 0.0f;
			subtitleIndex_ = 0;
		}

		break;
	case DAY::DAY4:

		if (18.0f <= subtitleDeltatime_ && 0 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0001.png", true);
			subtitleIndex_++;
		}

		if (19.5f <= subtitleDeltatime_ && 1 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0002.png", true);
			subtitleIndex_++;
		}

		if (21.5f <= subtitleDeltatime_ && 2 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0003.png", true);
			subtitleIndex_++;
		}

		if (26.5f <= subtitleDeltatime_ && 3 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0004.png", true);
			subtitleIndex_++;
		}

		if (30.5f <= subtitleDeltatime_ && 4 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0005.png", true);
			subtitleIndex_++;
		}

		if (35.5f <= subtitleDeltatime_ && 5 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0006.png", true);
			subtitleIndex_++;
		}

		if (38.2f <= subtitleDeltatime_ && 6 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0007.png", true);
			subtitleIndex_++;
		}

		if (42.2f <= subtitleDeltatime_ && 7 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0008.png", true);
			subtitleIndex_++;
		}

		if (45.2f <= subtitleDeltatime_ && 8 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0009.png", true);
			subtitleIndex_++;
		}

		if (48.5f <= subtitleDeltatime_ && 9 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0010.png", true);
			subtitleIndex_++;
		}

		if (53.0f <= subtitleDeltatime_ && 10 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0011.png", true);
			subtitleIndex_++;
		}

		if (55.0f <= subtitleDeltatime_ && 11 == subtitleIndex_)
		{
			UIController_->subtitleRenderer_->On();
			UIController_->subtitleRenderer_->SetImage("DAY4_0012.png", true);
			subtitleIndex_++;
		}

		if (60.0f <= subtitleDeltatime_ && 12 == subtitleIndex_)
		{
			isMuted_ = true;
			subtitleDeltatime_ = 0.0f;
			subtitleIndex_ = 0;
		}
		break;
	case DAY::DAY5:
		break;
	case DAY::DAY6:
		break;
	case DAY::CUSTOM:
		isMuted_ = true;
		break;
	case DAY::MAX:
		break;
	default:
		break;
	}

	
}