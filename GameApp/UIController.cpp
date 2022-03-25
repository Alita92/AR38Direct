#include "PreCompile.h"
#include "UIController.h"

#include <GameEngine/GameEngineUIRenderer.h>

UIController::UIController() // default constructer 디폴트 생성자
{

}

UIController::~UIController() // default destructer 디폴트 소멸자
{

}


void UIController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 0.0f });
	ImageInit();
}

void UIController::ImageInit()
{
	timeTenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	timeTenRenderer_->SetImage("M1.png", true);
	timeTenRenderer_->GetTransform()->SetLocalPosition({ 510.0f, 315.0f, 0.0f });

	timeOneRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	timeOneRenderer_->SetImage("M2.png", true);
	timeOneRenderer_->GetTransform()->SetLocalPosition({ 535.0f, 315.0f, 0.0f });

	amRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	amRenderer_->SetImage("UIAM.png", true);
	amRenderer_->GetTransform()->SetLocalPosition({ 580.0f, 315.0f, 0.0f });

	CCTVButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	CCTVButtonRenderer_->SetImage("UICCTVButton.png", true);
	CCTVButtonRenderer_->GetTransform()->SetLocalPosition({0.0f,-310.0f,0.0f});

	muteCallRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	muteCallRenderer_->SetImage("UIMuteCall.png", true);
	muteCallRenderer_->GetTransform()->SetLocalPosition({-550.0f, 320.0f, 0.0f});

	nightTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	nightTypoRenderer_->SetImage("UINight.png", true);
	nightTypoRenderer_->GetTransform()->SetLocalPosition({ 540.0f, 275.0f, 0.0f });

	nightNumRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	nightNumRenderer_->SetImage("S1.png", true);
	nightNumRenderer_->GetTransform()->SetLocalPosition({ 590.0f, 275.0f, 0.0f });

	powerLeftTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLeftTypoRenderer_->SetImage("UIPowerLeft.png", true);
	powerLeftTypoRenderer_->GetTransform()->SetLocalPosition({ -530.0f, -280.0f, 0.0f });

	powerLeftHundredRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLeftHundredRenderer_->SetImage("SM1.png", true);
	powerLeftHundredRenderer_->GetTransform()->SetLocalPosition({ -445.0f, -280.0f, 0.0f });

	powerLeftTenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLeftTenRenderer_->SetImage("SM0.png", true);
	powerLeftTenRenderer_->GetTransform()->SetLocalPosition({ -425.0F, -280.0f, 0.0f });

	powerLeftOneRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLeftOneRenderer_->SetImage("SM0.png", true);
	powerLeftOneRenderer_->GetTransform()->SetLocalPosition({ -405.0f, -280.0f, 0.0f });

	powerLeftPercentageRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLeftPercentageRenderer_->SetImage("UIPercentage.png", true);
	powerLeftPercentageRenderer_->GetTransform()->SetLocalPosition({ -385.0f, -280.0f, 0.0f });

	powerUsageTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerUsageTypoRenderer_->SetImage("UIUsage.png", true);
	powerUsageTypoRenderer_->GetTransform()->SetLocalPosition({ -563.0f, -315.0f, 0.0f });

	powerUsageLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerUsageLevelRenderer_->SetImage("UIPower1.png", true);
	powerUsageLevelRenderer_->GetTransform()->SetLocalPosition({ -465.0f, -315.0f, 0.0f });
}