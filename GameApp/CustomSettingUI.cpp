#include "PreCompile.h"
#include "CustomSettingUI.h"
#include "ENUM.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>
CustomSettingUI::CustomSettingUI() // default constructer 디폴트 생성자
	: clearScreen_(nullptr)
	, customizeNight_(nullptr)
	, nameFreddy_(nullptr)
	, portraitFreddy_(nullptr)
	, AILevelFreddyBanner_(nullptr)
	, nameBonnie_(nullptr)
	, portraitBonnie_(nullptr)
	, AILevelBonnieBanner_(nullptr)
	, nameChica_(nullptr)
	, portraitChica_(nullptr)
	, AILevelChicaBanner_(nullptr)
	, nameFoxy_(nullptr)
	, portraitFoxy_(nullptr)
	, AILevelFoxyBanner_(nullptr)
	, Instruction_(nullptr)
	, AIButtonFreddyL_(nullptr)
	, AIButtonFreddyLCollision_(nullptr)
	, AIButtonFreddyR_(nullptr)
	, AIButtonFreddyRCollision_(nullptr)
	, AIButtonBonnieL_(nullptr)
	, AIButtonBonnieLCollision_(nullptr)
	, AIButtonBonnieR_(nullptr)
	, AIButtonBonnieRCollision_(nullptr)
	, AIButtonChicaL_(nullptr)
	, AIButtonChicaLCollision_(nullptr)
	, AIButtonChicaR_(nullptr)
	, AIButtonChicaRCollision_(nullptr)
	, AIButtonFoxyL_(nullptr)
	, AIButtonFoxyLCollision_(nullptr)
	, AIButtonFoxyR_(nullptr)
	, AIButtonFoxyRCollision_(nullptr)
	, ReadyButton_(nullptr)
	, ReadyButtonCollision_(nullptr)
	, AINumberTenFreddy_(nullptr)
	, AINumberOneFreddy_(nullptr)
	, AINumberTenBonnie_(nullptr)
	, AINumberOneBonnie_(nullptr)
	, AINumberTenChica_(nullptr)
	, AINumberOneChica_(nullptr)
	, AINumberTenFoxy_(nullptr)
	, AINumberOneFoxy_(nullptr)
	, AILevelFreddy_(0)
	, AILevelBonnie_(0)
	, AILevelChica_(0)
	, AILevelFoxy_(0)
{

}

CustomSettingUI::~CustomSettingUI() // default destructer 디폴트 소멸자
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
	{
		AIButtonFreddyLCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonFreddyLCollision_->GetTransform()->SetLocalPosition(AIButtonFreddyL_->GetTransform()->GetLocalPosition());
		AIButtonFreddyLCollision_->GetTransform()->SetLocalScaling(AIButtonFreddyL_->GetTransform()->GetLocalScaling());
		AIButtonFreddyLCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		AIButtonFreddyRCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonFreddyRCollision_->GetTransform()->SetLocalPosition(AIButtonFreddyR_->GetTransform()->GetLocalPosition());
		AIButtonFreddyRCollision_->GetTransform()->SetLocalScaling(AIButtonFreddyR_->GetTransform()->GetLocalScaling());
		AIButtonFreddyRCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		AIButtonBonnieLCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonBonnieLCollision_->GetTransform()->SetLocalPosition(AIButtonBonnieL_->GetTransform()->GetLocalPosition());
		AIButtonBonnieLCollision_->GetTransform()->SetLocalScaling(AIButtonBonnieL_->GetTransform()->GetLocalScaling());
		AIButtonBonnieLCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		AIButtonBonnieRCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonBonnieRCollision_->GetTransform()->SetLocalPosition(AIButtonBonnieR_->GetTransform()->GetLocalPosition());
		AIButtonBonnieRCollision_->GetTransform()->SetLocalScaling(AIButtonBonnieR_->GetTransform()->GetLocalScaling());
		AIButtonBonnieRCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		AIButtonChicaLCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonChicaLCollision_->GetTransform()->SetLocalPosition(AIButtonChicaL_->GetTransform()->GetLocalPosition());
		AIButtonChicaLCollision_->GetTransform()->SetLocalScaling(AIButtonChicaL_->GetTransform()->GetLocalScaling());
		AIButtonChicaLCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		AIButtonChicaRCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonChicaRCollision_->GetTransform()->SetLocalPosition(AIButtonChicaR_->GetTransform()->GetLocalPosition());
		AIButtonChicaRCollision_->GetTransform()->SetLocalScaling(AIButtonChicaR_->GetTransform()->GetLocalScaling());
		AIButtonChicaRCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		AIButtonFoxyLCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonFoxyLCollision_->GetTransform()->SetLocalPosition(AIButtonFoxyL_->GetTransform()->GetLocalPosition());
		AIButtonFoxyLCollision_->GetTransform()->SetLocalScaling(AIButtonFoxyL_->GetTransform()->GetLocalScaling());
		AIButtonFoxyLCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		AIButtonFoxyRCollision_ = CreateTransformComponent<GameEngineCollision>();
		AIButtonFoxyRCollision_->GetTransform()->SetLocalPosition(AIButtonFoxyR_->GetTransform()->GetLocalPosition());
		AIButtonFoxyRCollision_->GetTransform()->SetLocalScaling(AIButtonFoxyR_->GetTransform()->GetLocalScaling());
		AIButtonFoxyRCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		ReadyButtonCollision_ = CreateTransformComponent<GameEngineCollision>();
		ReadyButtonCollision_->GetTransform()->SetLocalPosition(ReadyButton_->GetTransform()->GetLocalPosition());
		ReadyButtonCollision_->GetTransform()->SetLocalScaling(ReadyButton_->GetTransform()->GetLocalScaling());
		ReadyButtonCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}
}

void CustomSettingUI::Start()
{
	GetTransform()->SetWorldPosition({ 0.f,0.f,0.f });

	ImageInit();
	CollisionInit();
}

void CustomSettingUI::Update(float _Deltatime)
{
	LevelCheckUpdate();
}

void CustomSettingUI::LevelCheckUpdate()
{
	{
		if (10 <= AILevelFreddy_)
		{
			AINumberTenFreddy_->On();
			AINumberTenFreddy_->SetImage("AINumber" + std::to_string(AILevelFreddy_ / 10) + ".png", true);
		}
		else if (10 > AILevelFreddy_)
		{
			AINumberTenFreddy_->Off();
		}
		
		AINumberOneFreddy_->SetImage("AINumber" + std::to_string(AILevelFreddy_ % 10) + ".png", true);

	}

	{
		if (10 <= AILevelBonnie_)
		{
			AINumberTenBonnie_->On();
			AINumberTenBonnie_->SetImage("AINumber" + std::to_string(AILevelBonnie_ / 10) + ".png", true);
		}
		else if (10 > AILevelBonnie_)
		{
			AINumberTenBonnie_->Off();
		}

		AINumberOneBonnie_->SetImage("AINumber" + std::to_string(AILevelBonnie_ % 10) + ".png", true);
	}

	{
		if (10 <= AILevelChica_)
		{
			AINumberTenChica_->On();
			AINumberTenChica_->SetImage("AINumber" + std::to_string(AILevelChica_ / 10) + ".png", true);
		}
		else if (10 > AILevelChica_)
		{
			AINumberTenChica_->Off();
		}

		AINumberOneChica_->SetImage("AINumber" + std::to_string(AILevelChica_ % 10) + ".png", true);
	}

	{
		if (10 <= AILevelFoxy_)
		{
			AINumberTenFoxy_->On();
			AINumberTenFoxy_->SetImage("AINumber" + std::to_string(AILevelFoxy_ / 10) + ".png", true);
		}
		else if (10 > AILevelFoxy_)
		{
			AINumberTenFoxy_->Off();
		}

		AINumberOneFoxy_->SetImage("AINumber" + std::to_string(AILevelFoxy_ % 10) + ".png", true);
	}
}
