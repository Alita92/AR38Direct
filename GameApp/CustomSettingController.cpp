#include "PreCompile.h"
#include "CustomSettingController.h"
#include "ENUM.h"
#include "GameStaticData.h"
#include <GameEngine/GameEngineCollision.h>

#include "CustomSettingUI.h"
#include "GameMouse.h"

CustomSettingController::CustomSettingController() // default constructer 디폴트 생성자
	: customSettingUI_(nullptr), settingMouse_(nullptr)
{

}

CustomSettingController::~CustomSettingController() // default destructer 디폴트 소멸자
{

}

void CustomSettingController::ActorInit()
{

	settingMouse_ = GetLevel()->CreateActor<GameMouse>();
	settingMouse_->GetUIRenderer()->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));

	customSettingUI_ = GetLevel()->CreateActor<CustomSettingUI>();

}

void CustomSettingController::Reloading()
{

}

void CustomSettingController::Start()
{
	ActorInit();
}

void CustomSettingController::Update(float _DeltaTime)
{
	{
		customSettingUI_->AIButtonFreddyLCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionFreddyLvDown, this, std::placeholders::_1));

		customSettingUI_->AIButtonFreddyRCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionFreddyLvUp, this, std::placeholders::_1));

		customSettingUI_->AIButtonBonnieLCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionBonnieLvDown, this, std::placeholders::_1));

		customSettingUI_->AIButtonBonnieRCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionBonnieLvUp, this, std::placeholders::_1));

		customSettingUI_->AIButtonChicaLCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionChicaLvDown, this, std::placeholders::_1));

		customSettingUI_->AIButtonChicaRCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionChicaLvUp, this, std::placeholders::_1));

		customSettingUI_->AIButtonFoxyLCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionFoxyLvDown, this, std::placeholders::_1));

		customSettingUI_->AIButtonFoxyRCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionFoxyLvUp, this, std::placeholders::_1));


		customSettingUI_->ReadyButtonCollision_->Collision(
			CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&CustomSettingController::CollisionReady, this, std::placeholders::_1));
	}
}


void CustomSettingController::CollisionFreddyLvUp(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelFreddy_++;
	}
}

void CustomSettingController::CollisionFreddyLvDown(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelFreddy_--;
	}
}

void CustomSettingController::CollisionBonnieLvUp(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelBonnie_++;
	}
}

void CustomSettingController::CollisionBonnieLvDown(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelBonnie_--;
	}
}

void CustomSettingController::CollisionChicaLvUp(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelChica_++;
	}
}

void CustomSettingController::CollisionChicaLvDown(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelChica_--;
	}
}

void CustomSettingController::CollisionFoxyLvUp(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelFoxy_++;
	}
}

void CustomSettingController::CollisionFoxyLvDown(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		customSettingUI_->AILevelFoxy_--;
	}
}

void CustomSettingController::CollisionReady(GameEngineCollision* _other)
{

	GameStaticData::AICustomStartLevelFreddy_ = customSettingUI_->AILevelFreddy_;
	GameStaticData::AICustomStartLevelBonnie_ = customSettingUI_->AILevelBonnie_;
	GameStaticData::AICustomStartLevelChica_ = customSettingUI_->AILevelChica_;
	GameStaticData::AICustomStartLevelFoxy_ = customSettingUI_->AILevelFoxy_;

	GameStaticData::curDay_ = DAY::CUSTOM;

	GetLevel()->RequestLevelChange("Intermission");
}