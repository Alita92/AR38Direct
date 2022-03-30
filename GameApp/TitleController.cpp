#include "PreCompile.h"
#include "TitleController.h"
#include <GameEngine/GameEngineCollision.h>

#include "TitleFreddy.h"
#include "TitleText.h"
#include "TitleNewsPaper.h"

#include "ENUM.h"

TitleController::TitleController() // default constructer 디폴트 생성자
	: titleFreddy_(nullptr), titleText_(nullptr), titleNewsPaper_(nullptr)
{

}

TitleController::~TitleController() // default destructer 디폴트 소멸자
{

}

void TitleController::ActorInit()
{
	titleFreddy_ = GetLevel()->CreateActor<TitleFreddy>();
	titleText_ = GetLevel()->CreateActor<TitleText>();
	titleNewsPaper_ = GetLevel()->CreateActor<TitleNewsPaper>();
}


void TitleController::Start()
{
	ActorInit();
}

void TitleController::Update(float _Deltatime)
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
}

void TitleController::CollisionNewGame(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		GetLevel()->RequestLevelChange("Play");
	}
}

void TitleController::CollisionContinue(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		GetLevel()->RequestLevelChange("Play");
	}
}

void TitleController::CollisionCustomNight(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		GetLevel()->RequestLevelChange("CustomSetting");
	}
}


