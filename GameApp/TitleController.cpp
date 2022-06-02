#include "PreCompile.h"
#include "TitleController.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include "TitleFreddy.h"
#include "TitleText.h"
#include "TitleNewsPaper.h"
#include "GameMouse.h"
#include "FadeScreen.h"
#include "GlitchScreen.h"
#include "ENUM.h"



#include "GameStaticData.h"

TitleController::TitleController() // default constructer 디폴트 생성자
	: titleMouse_(nullptr)
	, titleFreddy_(nullptr)
	, titleText_(nullptr)
	, titleNewsPaper_(nullptr)
	, deltaTime_(0.0f)
	, state_(this)
	, alphaChangeTime_(1.0f)
	, fadeScreen_(nullptr)
	, glitchScreen_(nullptr)
	, isDark_(false)
	, isDebugOn_(false)
{

}

TitleController::~TitleController() // default destructer 디폴트 소멸자
{

}

void TitleController::ActorInit()
{
	glitchScreen_ = GetLevel()->CreateActor<GlitchScreen>();

	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(0.0f);

	titleMouse_ = GetLevel()->CreateActor<GameMouse>();
	titleMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));

	titleFreddy_ = GetLevel()->CreateActor<TitleFreddy>();
	titleText_ = GetLevel()->CreateActor<TitleText>();
	titleNewsPaper_ = GetLevel()->CreateActor<TitleNewsPaper>();
}

void TitleController::StateInit()
{
	state_.CreateState("SceneReady", &TitleController::startSceneReady, &TitleController::updateSceneReady);
	state_.CreateState("Idle", &TitleController::startIdle, &TitleController::updateIdle);
	state_.CreateState("NewData", &TitleController::startNewData, &TitleController::updateNewData);
	state_.CreateState("NewGame", &TitleController::startNewGame, &TitleController::updateNewGame);
	state_.CreateState("Continue", &TitleController::startContinue, &TitleController::updateContinue);
	state_.CreateState("CustomNight", &TitleController::startCustomNight, &TitleController::updateCustomNight);
	state_.CreateState("6thNight", &TitleController::start6thNight, &TitleController::update6thNight);

	state_.ChangeState("SceneReady");
}


void TitleController::ControllerReloading()
{
	state_.ChangeState("SceneReady");
	fadeScreen_->SetAlpha(0.0f);
	fadeScreen_->StartDark(0.0f);
	fadeScreen_->Reset();

	titleMouse_->On();
	titleMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));

	alphaChangeTime_ = 1.0f;
	deltaTime_ = 0.0f;

	{
		titleFreddy_->isGameStarted_ = false;

		titleText_->titleNewGameCollision_->On();
		titleText_->titleContinueCollision_->On();
		titleText_->titleCustomNightCollision_->On();
		titleText_->title6thNightCollision_->On();
	}

	{
		titleFreddy_->titleFreddyImageRenderer_->SetAlpha(1.0f);
		titleText_->titleName_->SetAlpha(1.0f);
		titleText_->titleNewGame_->SetAlpha(1.0f);
		titleText_->titleContinue_->SetAlpha(1.0f);
		titleText_->titleCustomNight_->SetAlpha(1.0f);
		titleText_->title6thNight_->SetAlpha(1.0f);
		titleText_->titleScott_->SetAlpha(1.0f);
		titleText_->titleArrow_->SetAlpha(1.0f);
		glitchScreen_->whiteNoiseRenderer_->SetAlpha(1.0f / 2.0f);
		glitchScreen_->scanLineRenderer_->SetAlpha(1.0f / 5.0f);
		glitchScreen_->subScanLineRenderer_->SetAlpha(1.0f / 5.0f);
	}

	isDark_ = false;
	ambientPlayer_.Stop();
	musicPlayer_.Stop();
}


void TitleController::Start()
{
	ActorInit();
	StateInit();
}

void TitleController::Update(float _Deltatime)
{
	state_.Update();
	DebugRenderUpdate();
}

void TitleController::CollisionNewGame(GameEngineCollision* _other)
{
	titleText_->titleArrow_->On();
	titleText_->titleArrow_->GetTransform()->SetLocalPosition({ -520.0f, -60.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		state_.ChangeState("NewData");
	}

}

void TitleController::CollisionContinue(GameEngineCollision* _other)
{
	titleText_->titleArrow_->On();
	titleText_->titleArrow_->GetTransform()->SetLocalPosition({ -520.0f, -130.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		state_.ChangeState("Continue");
	}
}

void TitleController::CollisionCustomNight(GameEngineCollision* _other)
{
	titleText_->titleArrow_->On();
	titleText_->titleArrow_->GetTransform()->SetLocalPosition({ -520.0f, -280.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		state_.ChangeState("CustomNight");
	}
}


void TitleController::CollisionNewDataYes(GameEngineCollision* _other)
{
	titleText_->titleArrow_->On();
	titleText_->titleArrow_->GetTransform()->SetLocalPosition({ -520.0f, -130.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		awakePlayer_.PlayOverLap("CCTVSwitch.wav");
		state_.ChangeState("NewGame");
	}
}

void TitleController::CollisionNewDataNo(GameEngineCollision* _other)
{
	titleText_->titleArrow_->On();
	titleText_->titleArrow_->GetTransform()->SetLocalPosition({ -520.0f, -210.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	{
		if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
		{
			state_.ChangeState("Idle");
		}
	}
}

void TitleController::UpdateTitleAlphaChange()
{
	if (0.0f <= alphaChangeTime_)
	{
		alphaChangeTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		titleFreddy_->titleFreddyImageRenderer_->SetAlpha(alphaChangeTime_);
		titleText_->titleName_->SetAlpha(alphaChangeTime_);
		titleText_->titleNewGame_->SetAlpha(alphaChangeTime_);
		titleText_->titleContinue_->SetAlpha(alphaChangeTime_);
		titleText_->titleCustomNight_->SetAlpha(alphaChangeTime_);
		titleText_->title6thNight_->SetAlpha(alphaChangeTime_);
		titleText_->titleScott_->SetAlpha(alphaChangeTime_);
		titleText_->titleArrow_->SetAlpha(alphaChangeTime_);
		titleText_->titleNewData_->SetAlpha(alphaChangeTime_);
		titleText_->titleYes_->SetAlpha(alphaChangeTime_);
		titleText_->titleNo_->SetAlpha(alphaChangeTime_);
		glitchScreen_->whiteNoiseRenderer_->SetAlpha(alphaChangeTime_/2);
		glitchScreen_->scanLineRenderer_->SetAlpha(alphaChangeTime_ / 5);
		glitchScreen_->subScanLineRenderer_->SetAlpha(alphaChangeTime_ / 5);
	}
}

StateInfo TitleController::startSceneReady(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::updateSceneReady(StateInfo _state)
{
	return "Idle";
}

StateInfo TitleController::startIdle(StateInfo _state)
{
	titleText_->titleNewGame_->On();
	titleText_->titleContinue_->On();
	titleText_->title6thNight_->On();
	titleText_->titleCustomNight_->On();
	titleText_->titleNewGameCollision_->On();
	titleText_->titleContinueCollision_->On();
	titleText_->titleCustomNightCollision_->On();
	titleText_->title6thNightCollision_->On();

	titleText_->titleNewData_->Off();
	titleText_->titleYes_->Off();
	titleText_->titleNo_->Off();
	titleText_->titleYesCollision_->Off();
	titleText_->titleNoCollision_->Off();

	glitchScreen_->PlayWhiteNoise(true);
	glitchScreen_->SetWhiteNoiseAlpha(0.4f);
	glitchScreen_->SetSubRenderer(true);

	ambientPlayer_.PlayAlone("StaticLong.wav");
	musicPlayer_.PlayAlone("TitleMusic.wav");
	return StateInfo();
}

StateInfo TitleController::updateIdle(StateInfo _state)
{

	glitchScreen_->ScanLineRandomChange();

	{
		titleText_->titleNewGameCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionNewGame, this, std::placeholders::_1));

		titleText_->titleContinueCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionContinue, this, std::placeholders::_1));

		titleText_->titleCustomNightCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionCustomNight, this, std::placeholders::_1));

		titleText_->title6thNightCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionCustomNight, this, std::placeholders::_1));
	}

	return StateInfo();
}

StateInfo TitleController::startNewData(StateInfo _state)
{
	titleText_->titleArrow_->Off();
	titleText_->titleNewGame_->Off();
	titleText_->titleContinue_->Off();
	titleText_->title6thNight_->Off();
	titleText_->titleCustomNight_->Off();

	titleText_->titleNewGameCollision_->Off();
	titleText_->titleContinueCollision_->Off();
	titleText_->titleCustomNightCollision_->Off();
	titleText_->title6thNightCollision_->Off();

	titleText_->titleNewData_->On();
	titleText_->titleYes_->On();
	titleText_->titleNo_->On();
	titleText_->titleYesCollision_->On();
	titleText_->titleNoCollision_->On();

	return StateInfo();
}

StateInfo TitleController::updateNewData(StateInfo _state)
{

	titleText_->titleYesCollision_->Collision(
		CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionNewDataYes, this, std::placeholders::_1));

	titleText_->titleNoCollision_->Collision(
		CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleController::CollisionNewDataNo, this, std::placeholders::_1));
	return StateInfo();
}

StateInfo TitleController::startNewGame(StateInfo _state)
{
	deltaTime_ = 0.0f;
	titleFreddy_->isGameStarted_ = true;

	titleMouse_->Off();
	titleText_->titleNewGameCollision_->Off();
	titleText_->titleContinueCollision_->Off();
	titleText_->titleCustomNightCollision_->Off();
	titleText_->title6thNightCollision_->Off();

	GameStaticData::curDay_ = DAY::DAY1;

	return StateInfo();
}

StateInfo TitleController::updateNewGame(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();
	glitchScreen_->SetStatic();
	if (0.5f <= deltaTime_)
	{
		UpdateTitleAlphaChange();
	}

	if (3.0f <= deltaTime_)
	{
		if (false == isDark_)
		{
			fadeScreen_->StartDark(2.5f);
			isDark_ = true;
		}


		if (true == fadeScreen_->isFullDark_)
		{
			StopAllSound();

			GetLevel()->RequestLevelChange("Intermission");
		}
	}

	return StateInfo();
}

StateInfo TitleController::startContinue(StateInfo _state)
{
	deltaTime_ = 0.0f;
	titleFreddy_->isGameStarted_ = true;

	titleMouse_->Off();
	titleText_->titleNewGameCollision_->Off();
	titleText_->titleContinueCollision_->Off();
	titleText_->titleCustomNightCollision_->Off();
	titleText_->title6thNightCollision_->Off();

	GameStaticData::LoadDay();
	return StateInfo();
}

StateInfo TitleController::updateContinue(StateInfo _state)
{
	StopAllSound();
	GetLevel()->RequestLevelChange("Intermission");

	return StateInfo();
}

StateInfo TitleController::startCustomNight(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::updateCustomNight(StateInfo _state)
{
	StopAllSound();
	GetLevel()->RequestLevelChange("CustomSetting");
	return "Idle";
}

StateInfo TitleController::start6thNight(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::update6thNight(StateInfo _state)
{
	return StateInfo();
}

void TitleController::DebugRenderUpdate()
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_RECT"))
	{
		isDebugOn_ = !isDebugOn_;
	}

	if (true == isDebugOn_)
	{
		GetLevel()->PushDebugRender(titleText_->titleNewGameCollision_->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(titleText_->titleContinueCollision_->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(titleText_->titleCustomNightCollision_->GetTransform(), CollisionType::Rect);
		GetLevel()->PushDebugRender(titleText_->title6thNightCollision_->GetTransform(), CollisionType::Rect);
	}

}
