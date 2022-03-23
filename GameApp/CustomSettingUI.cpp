#include "PreCompile.h"
#include "CustomSettingUI.h"
#include "ENUM.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

CustomSettingUI::CustomSettingUI() // default constructer 디폴트 생성자
{

}

CustomSettingUI::~CustomSettingUI() // default destructer 디폴트 소멸자
{

}

CustomSettingUI::CustomSettingUI(CustomSettingUI&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void CustomSettingUI::ImageInit()
{
	clearScreen_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	clearScreen_->SetImage("ClearScreen.png", true);
	clearScreen_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 100.0f });

	customizeNight_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	customizeNight_->SetImage("CustomizeNight.png", true);
	customizeNight_->GetTransform()->SetLocalPosition({ 0.0f, 300.0f, 0.0f });

	nameFreddy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	nameFreddy_->SetImage("NameFreddy.png", true);
	nameFreddy_->GetTransform()->SetLocalPosition({-448.0f, 220.0f, 0.0f});

	portraitFreddy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	portraitFreddy_->SetImage("PortraitFreddy.png", true);
	portraitFreddy_->GetTransform()->SetLocalPosition({ -448.0f, 70.0f, 0.0f });

	AILevelFreddyBanner_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AILevelFreddyBanner_->SetImage("AILevel.png", true);
	AILevelFreddyBanner_->GetTransform()->SetLocalPosition({ -448.0f, -70.0f, 0.0f });

	nameBonnie_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	nameBonnie_->SetImage("NameBonnie.png", true);
	nameBonnie_->GetTransform()->SetLocalPosition({ -152.0f, 225.0f, 0.0f });

	portraitBonnie_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	portraitBonnie_->SetImage("PortraitBonnie.png", true);
	portraitBonnie_->GetTransform()->SetLocalPosition({ -152.0f, 70.0f, 0.0f });

	AILevelBonnieBanner_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AILevelBonnieBanner_->SetImage("AILevel.png", true);
	AILevelBonnieBanner_->GetTransform()->SetLocalPosition({ -152.0f, -70.0f, 0.0f });

	nameChica_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	nameChica_->SetImage("NameChica.png", true);
	nameChica_->GetTransform()->SetLocalPosition({ 144.0f, 225.0f, 0.0f });

	portraitChica_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	portraitChica_->SetImage("PortraitChica.png", true);
	portraitChica_->GetTransform()->SetLocalPosition({ 144.0f, 70.0f, 0.0f });

	AILevelChicaBanner_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AILevelChicaBanner_->SetImage("AILevel.png", true);
	AILevelChicaBanner_->GetTransform()->SetLocalPosition({ 144.0f, -70.0f, 0.0f });

	nameFoxy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	nameFoxy_->SetImage("NameFoxy.png", true);
	nameFoxy_->GetTransform()->SetLocalPosition({ 440.0f, 220.0f, 0.0f });

	portraitFoxy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	portraitFoxy_->SetImage("PortraitFoxy.png", true);
	portraitFoxy_->GetTransform()->SetLocalPosition({ 440.0f, 70.0f, 0.0f });

	AILevelFoxyBanner_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AILevelFoxyBanner_->SetImage("AILevel.png", true);
	AILevelFoxyBanner_->GetTransform()->SetLocalPosition({ 440.0f, -70.0f, 0.0f });

	Instruction_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	Instruction_->SetImage("Instruction.png", true);
	Instruction_->GetTransform()->SetLocalPosition({ 0.0f, -215.0f, 0.0f });


	AIButtonFreddyL_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonFreddyL_->SetImage("AIButtonL.png", true);
	AIButtonFreddyL_->GetTransform()->SetLocalPosition({ -548.0f, -135.0f, 0.0f });

	AIButtonFreddyR_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonFreddyR_->SetImage("AIButtonR.png", true);
	AIButtonFreddyR_->GetTransform()->SetLocalPosition({ -348.0f, -135.0f, 0.0f });

	AIButtonBonnieL_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonBonnieL_->SetImage("AIButtonL.png", true);
	AIButtonBonnieL_->GetTransform()->SetLocalPosition({ -252.0f, -135.0f, 0.0f });

	AIButtonBonnieR_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonBonnieR_->SetImage("AIButtonR.png", true);
	AIButtonBonnieR_->GetTransform()->SetLocalPosition({ -52.0f, -135.0f, 0.0f });

	AIButtonChicaL_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonChicaL_->SetImage("AIButtonL.png", true);
	AIButtonChicaL_->GetTransform()->SetLocalPosition({ 44.0f, -135.0f, 0.0f });

	AIButtonChicaR_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonChicaR_->SetImage("AIButtonR.png", true);
	AIButtonChicaR_->GetTransform()->SetLocalPosition({ 244.0f, -135.0f, 0.0f });

	AIButtonFoxyL_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonFoxyL_->SetImage("AIButtonL.png", true);
	AIButtonFoxyL_->GetTransform()->SetLocalPosition({ 340.0f, -135.0f, 0.0f });

	AIButtonFoxyR_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AIButtonFoxyR_->SetImage("AIButtonR.png", true);
	AIButtonFoxyR_->GetTransform()->SetLocalPosition({ 540.0f, -135.0f, 0.0f });

	ReadyButton_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ReadyButton_->SetImage("ReadyButton.png", true);
	ReadyButton_->GetTransform()->SetLocalPosition({ 0.0f, -330.0f, 0.0f });

	AINumberTenFreddy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	AINumberOneFreddy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AINumberOneFreddy_->SetImage("AINumber0.png", true);
	AINumberOneFreddy_->GetTransform()->SetLocalPosition({ -448.0f, -135.0f, 0.0f });

	AINumberTenBonnie_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	AINumberOneBonnie_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AINumberOneBonnie_->SetImage("AINumber0.png", true);
	AINumberOneBonnie_->GetTransform()->SetLocalPosition({ -152.0f, -135.0f, 0.0f });

	AINumberTenChica_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	AINumberOneChica_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AINumberOneChica_->SetImage("AINumber0.png", true);
	AINumberOneChica_->GetTransform()->SetLocalPosition({ 144.0f, -135.0f, 0.0f });

	AINumberTenFoxy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	AINumberOneFoxy_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	AINumberOneFoxy_->SetImage("AINumber0.png", true);
	AINumberOneFoxy_->GetTransform()->SetLocalPosition({ 440.0f, -135.0f, 0.0f });
}



void CustomSettingUI::CollisionInit()
{

}

void CustomSettingUI::Start()
{
	GetTransform()->SetWorldPosition({ 0.f,0.f,0.f });

	ImageInit();
	CollisionInit();
}

void CustomSettingUI::Update(float _Deltatime)
{
	CollisionCheckUpdate();
	DebugRenderUpdate();
}

void CustomSettingUI::DebugRenderUpdate()
{
#ifdef _DEBUG
	//GetLevel()->PushDebugRender(titleNewGameCollision_->GetTransform(), CollisionType::Rect);
	//GetLevel()->PushDebugRender(titleContinueCollision_->GetTransform(), CollisionType::Rect);
#endif
}

void CustomSettingUI::CollisionCheckUpdate()
{

}

void CustomSettingUI::CollisionAIButtonFreddyL(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonFreddyR(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonBonnieL(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonBonnieR(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonChicaL(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonChicaR(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonFoxyL(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionAIButtonFoxyR(GameEngineCollision* _other)
{

}

void CustomSettingUI::CollisionReadyButton(GameEngineCollision* _other)
{

}