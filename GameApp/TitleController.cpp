#include "PreCompile.h"
#include "TitleController.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>
#include "TitleFreddy.h"
#include "TitleText.h"
#include "TitleNewsPaper.h"
#include "GameMouse.h"

#include "ENUM.h"

TitleController::TitleController() // default constructer 디폴트 생성자
	: titleMouse_(nullptr), titleFreddy_(nullptr), titleText_(nullptr), titleNewsPaper_(nullptr), deltaTime_(0.0f), state_(this), alphaChangeTime_(1.0f)
{

}

TitleController::~TitleController() // default destructer 디폴트 소멸자
{

}

void TitleController::ActorInit()
{
	titleMouse_ = GetLevel()->CreateActor<GameMouse>();
	titleMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	titleFreddy_ = GetLevel()->CreateActor<TitleFreddy>();
	titleText_ = GetLevel()->CreateActor<TitleText>();
	titleNewsPaper_ = GetLevel()->CreateActor<TitleNewsPaper>();

}

void TitleController::StateInit()
{
	state_.CreateState("Idle", &TitleController::startIdle, &TitleController::updateIdle);
	state_.CreateState("NewGame", &TitleController::startNewGame, &TitleController::updateNewGame);
	state_.CreateState("Continue", &TitleController::startContinue, &TitleController::updateContinue);
	state_.CreateState("CustomNight", &TitleController::startCustomNight, &TitleController::updateCustomNight);
	state_.CreateState("6thNight", &TitleController::start6thNight, &TitleController::update6thNight);

	state_.ChangeState("Idle");
}


void TitleController::Start()
{
	ActorInit();
	StateInit();
}

void TitleController::Update(float _Deltatime)
{

	state_.Update();

}

void TitleController::CollisionNewGame(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		state_.ChangeState("NewGame");
	}
}

void TitleController::CollisionContinue(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		state_.ChangeState("Continue");
	}
}

void TitleController::CollisionCustomNight(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		state_.ChangeState("CustomNight");
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
	}
}

StateInfo TitleController::startIdle(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::updateIdle(StateInfo _state)
{
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

StateInfo TitleController::startNewGame(StateInfo _state)
{
	deltaTime_ = 0.0f;

	titleMouse_->Off();

	titleFreddy_->isGameStarted_ = true;

	titleText_->titleNewGameCollision_->Off();
	titleText_->titleContinueCollision_->Off();
	titleText_->titleCustomNightCollision_->Off();
	titleText_->title6thNightCollision_->Off();

	return StateInfo();
}

StateInfo TitleController::updateNewGame(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (1.0f <= deltaTime_)
	{
		UpdateTitleAlphaChange();
	//	GetLevel()->RequestLevelChange("Play");
	}

	if (5.0f <= deltaTime_)
	{
		GetLevel()->RequestLevelChange("Intermission");
	}

	return StateInfo();
}

StateInfo TitleController::startContinue(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::updateContinue(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::startCustomNight(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::updateCustomNight(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::start6thNight(StateInfo _state)
{
	return StateInfo();
}

StateInfo TitleController::update6thNight(StateInfo _state)
{
	return StateInfo();
}