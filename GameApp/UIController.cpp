#include "PreCompile.h"
#include "UIController.h"
#include "ENUM.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

UIController::UIController() // default constructer 디폴트 생성자
	: timeTenRenderer_(nullptr)
	, timeOneRenderer_(nullptr)
	, amRenderer_(nullptr)
	, CCTVButtonRenderer_(nullptr)
	, CCTVButtonCollision_(nullptr)
	, muteCallRenderer_(nullptr)
	, muteCallCollision_(nullptr)
	, nightTypoRenderer_(nullptr)
	, nightNumRenderer_(nullptr)
	, powerRateTypoRenderer_(nullptr)
	, powerRateHundredRenderer_(nullptr)
	, powerRateTenRenderer_(nullptr)
	, powerRateOneRenderer_(nullptr)
	, powerRatePercentageRenderer_(nullptr)
	, powerLevelTypoRenderer_(nullptr)
	, powerLevelRenderer_(nullptr)
	, powerRateTenFlag_(false)
	, powerRateOneFlag_(false)
{

}

UIController::~UIController() // default destructer 디폴트 소멸자
{

}


void UIController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 0.0f });

	ImageInit();
	CollisionInit();
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

	powerRateTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateTypoRenderer_->SetImage("UIPowerLeft.png", true);
	powerRateTypoRenderer_->GetTransform()->SetLocalPosition({ -530.0f, -280.0f, 0.0f });
		 
	powerRateHundredRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateHundredRenderer_->SetImage("SM1.png", true);
	powerRateHundredRenderer_->GetTransform()->SetLocalPosition({ -445.0f, -280.0f, 0.0f });
		 
	powerRateTenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateTenRenderer_->SetImage("SM0.png", true);
	powerRateTenRenderer_->GetTransform()->SetLocalPosition({ -425.0F, -280.0f, 0.0f });
		 
	powerRateOneRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateOneRenderer_->SetImage("SM0.png", true);
	powerRateOneRenderer_->GetTransform()->SetLocalPosition({ -405.0f, -280.0f, 0.0f });
		 
	powerRatePercentageRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRatePercentageRenderer_->SetImage("UIPercentage.png", true);
	powerRatePercentageRenderer_->GetTransform()->SetLocalPosition({ -385.0f, -280.0f, 0.0f });

	powerLevelTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLevelTypoRenderer_->SetImage("UIUsage.png", true);
	powerLevelTypoRenderer_->GetTransform()->SetLocalPosition({ -563.0f, -315.0f, 0.0f });

	powerLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLevelRenderer_->SetImage("UIPower1.png", true);
	powerLevelRenderer_->GetTransform()->SetLocalPosition({ -465.0f, -315.0f, 0.0f });
}

void UIController::CollisionInit()
{
	{
		CCTVButtonCollision_ = CreateTransformComponent<GameEngineCollision>();
		CCTVButtonCollision_->GetTransform()->SetLocalPosition(CCTVButtonRenderer_->GetTransform()->GetLocalPosition());
		CCTVButtonCollision_->GetTransform()->SetLocalScaling(CCTVButtonRenderer_->GetTransform()->GetLocalScaling());
		CCTVButtonCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		muteCallCollision_ = CreateTransformComponent<GameEngineCollision>();
		muteCallCollision_->GetTransform()->SetLocalPosition(muteCallRenderer_->GetTransform()->GetLocalPosition());
		muteCallCollision_->GetTransform()->SetLocalPosition(muteCallRenderer_->GetTransform()->GetLocalScaling());
		muteCallCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}
}

void UIController::Update(float _DeltaTime)
{
	DebugRenderUpdate();
	CollisionCheckUpdate();
}

void UIController::DebugRenderUpdate()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(CCTVButtonCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(muteCallCollision_->GetTransform(), CollisionType::Rect);
#endif
}

void UIController::CollisionCheckUpdate()
{
	CCTVButtonCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&UIController::CollisionCCTVButton, this, std::placeholders::_1));
	muteCallCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&UIController::CollisionMuteCall, this, std::placeholders::_1));
}

void UIController::CollisionCCTVButton(GameEngineCollision* _other)
{

}

void UIController::CollisionMuteCall(GameEngineCollision* _other)
{

}


void UIController::SetTimeRenderer(int _curTime)
{
	if (0 > _curTime || 6 < _curTime)
	{
		GameEngineDebug::MsgBoxError("UIController 의 시간 렌더링 함수 SetTimeRenderer 파라미터에 0~6사이의 값이 아닌 다른 값이 들어갔습니다.");
	}
	if (0 == _curTime)
	{
		return;
	}
	else
	{
		timeTenRenderer_->Off();
		timeOneRenderer_->SetImage('M' + std::to_string(_curTime) + ".png", true);
		return;
	}
}

void UIController::SetPowerRateRenderer(float _curPowerRate)
{
	if (0 > _curPowerRate || 100.0f < _curPowerRate)
	{
		GameEngineDebug::MsgBoxError("UIController 의 전기 렌더링 함수 SetPowerRateRenderer 파라미터에 0 미만 100 초과 값이 들어갔습니다.");
	}
	if (100.0f == _curPowerRate)
	{
		return;
	}
	else if (100.0f > _curPowerRate && 10.0f <= _curPowerRate)
	{
		if (false == powerRateTenFlag_)
		{
			powerRateHundredRenderer_->Off();
			powerRateTenFlag_ = true;
		}

		powerRateTenRenderer_->SetImage("SM" + std::to_string(static_cast<int>(_curPowerRate) / 10) + ".png", true);
		powerRateOneRenderer_->SetImage("SM" + std::to_string(static_cast<int>(_curPowerRate) % 10) + ".png", true);
		return;
	}
	else if (10.0f > _curPowerRate)
	{
		if (false == powerRateOneFlag_)
		{
			powerRateTenRenderer_->Off();
			powerRateOneFlag_ = true;
		}

		powerRateOneRenderer_->SetImage("SM" + std::to_string(static_cast<int>(_curPowerRate)) + ".png", true);
		return;
	}
}

void UIController::SetPowerLevelRenderer(int _curPowerLevel)
{
	if (1 > _curPowerLevel || 5 < _curPowerLevel)
	{
		GameEngineDebug::MsgBoxError("UIController 의 전기사용량 렌더링 함수 SetPowerLevelRenderer 파라미터에 1 미만 5 초과 값이 들어갔습니다.");
	}
	
	powerLevelRenderer_->SetImage("UIPower" + std::to_string(_curPowerLevel) + ".png", true);
	return;
}