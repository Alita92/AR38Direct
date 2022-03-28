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
	, cameraDisabledRenderer_(nullptr)
	, recordingMarkRenderer_(nullptr)
	, cameraNameRenderer_(nullptr)
	, mapRenderer_(nullptr)
	, cam1AScreenRenderer_(nullptr)
	, cam1ARenderer_(nullptr)
	, cam1ACollision_(nullptr)
	, cam1BScreenRenderer_(nullptr)
	, cam1BRenderer_(nullptr)
	, cam1BCollision_(nullptr)
	, cam1CScreenRenderer_(nullptr)
	, cam1CRenderer_(nullptr)
	, cam1CCollision_(nullptr)
	, cam5ScreenRenderer_(nullptr)
	, cam5Renderer_(nullptr)
	, cam5Collision_(nullptr)
	, cam3ScreenRenderer_(nullptr)
	, cam3Renderer_(nullptr)
	, cam3Collision_(nullptr)
	, cam2AScreenRenderer_(nullptr)
	, cam2ARenderer_(nullptr)
	, cam2ACollision_(nullptr)
	, cam2BScreenRenderer_(nullptr)
	, cam2BRenderer_(nullptr)
	, cam2BCollision_(nullptr)
	, cam7ScreenRenderer_(nullptr)
	, cam7Renderer_(nullptr)
	, cam7Collision_(nullptr)
	, cam6ScreenRenderer_(nullptr)
	, cam6Renderer_(nullptr)
	, cam6Collision_(nullptr)
	, cam4AScreenRenderer_(nullptr)
	, cam4ARenderer_(nullptr)
	, cam4ACollision_(nullptr)
	, cam4BScreenRenderer_(nullptr)
	, cam4BRenderer_(nullptr)
	, cam4BCollision_(nullptr)
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
	timeTenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	
	timeOneRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	timeOneRenderer_->SetImage("M2.png", true);
	timeOneRenderer_->GetTransform()->SetLocalPosition({ 535.0f, 315.0f, 0.0f });
	timeOneRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	amRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	amRenderer_->SetImage("UIAM.png", true);
	amRenderer_->GetTransform()->SetLocalPosition({ 580.0f, 315.0f, 0.0f });
	amRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	CCTVButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	CCTVButtonRenderer_->SetImage("UICCTVButton.png", true);
	CCTVButtonRenderer_->GetTransform()->SetLocalPosition({0.0f,-310.0f,0.0f});
	CCTVButtonRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	muteCallRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	muteCallRenderer_->SetImage("UIMuteCall.png", true);
	muteCallRenderer_->GetTransform()->SetLocalPosition({-550.0f, 320.0f, 0.0f});
	muteCallRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	nightTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	nightTypoRenderer_->SetImage("UINight.png", true);
	nightTypoRenderer_->GetTransform()->SetLocalPosition({ 540.0f, 275.0f, 0.0f });
	nightTypoRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	nightNumRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	nightNumRenderer_->SetImage("S1.png", true);
	nightNumRenderer_->GetTransform()->SetLocalPosition({ 590.0f, 275.0f, 0.0f });
	nightNumRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	powerRateTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateTypoRenderer_->SetImage("UIPowerLeft.png", true);
	powerRateTypoRenderer_->GetTransform()->SetLocalPosition({ -530.0f, -280.0f, 0.0f });
	powerRateTypoRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	powerRateHundredRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateHundredRenderer_->SetImage("SM1.png", true);
	powerRateHundredRenderer_->GetTransform()->SetLocalPosition({ -445.0f, -280.0f, 0.0f });
	powerRateHundredRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	powerRateTenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateTenRenderer_->SetImage("SM0.png", true);
	powerRateTenRenderer_->GetTransform()->SetLocalPosition({ -425.0F, -280.0f, 0.0f });
	powerRateTenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
		 
	powerRateOneRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRateOneRenderer_->SetImage("SM0.png", true);
	powerRateOneRenderer_->GetTransform()->SetLocalPosition({ -405.0f, -280.0f, 0.0f });
	powerRateOneRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
		 
	powerRatePercentageRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerRatePercentageRenderer_->SetImage("UIPercentage.png", true);
	powerRatePercentageRenderer_->GetTransform()->SetLocalPosition({ -385.0f, -280.0f, 0.0f });
	powerRatePercentageRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	powerLevelTypoRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLevelTypoRenderer_->SetImage("UIUsage.png", true);
	powerLevelTypoRenderer_->GetTransform()->SetLocalPosition({ -563.0f, -315.0f, 0.0f });
	powerLevelTypoRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	powerLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	powerLevelRenderer_->SetImage("UIPower1.png", true);
	powerLevelRenderer_->GetTransform()->SetLocalPosition({ -465.0f, -315.0f, 0.0f });
	powerLevelRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));

	// CCTV 전용
	cameraDisabledRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cameraDisabledRenderer_->SetImage("CameraDisabled.png", true);
	cameraDisabledRenderer_->GetTransform()->SetLocalPosition({0.0f, 280.0f, 0.0f});
	cameraDisabledRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	//cameraDisabledRenderer_->Off();

	recordingMarkRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	recordingMarkRenderer_->SetImage("RecordingMark.png", true);
	recordingMarkRenderer_->GetTransform()->SetLocalPosition({ -520.0f, 300.0f, 0.0f });
	recordingMarkRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	//recordingMarkRenderer_->Off();

	cameraNameRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cameraNameRenderer_->SetImage("NameShowStage.png", true);
	cameraNameRenderer_->GetTransform()->SetLocalPosition({ 315.0f, 60.0f, 0.0f });
	cameraNameRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	//cameraNameRenderer_->Off();

	mapRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	mapRenderer_->SetImage("CCTVMap0.png", true);
	mapRenderer_->GetTransform()->SetLocalPosition({ 420.0f, -150.0f, 0.0f });
	mapRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	//mapRenderer_->Off();

	cam1AScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1AScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam1AScreenRenderer_->GetTransform()->SetLocalPosition({ 360.0f, 10.0f, 0.0f });
	cam1AScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam1AScreenRenderer_->Off();

	cam1ARenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1ARenderer_->SetImage("cam1A.png", true);
	cam1ARenderer_->GetTransform()->SetLocalPosition({ 360.0f, 10.0f, 0.0f });
	cam1ARenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam1AScreenRenderer_->Off();

	cam1BScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1BScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam1BScreenRenderer_->GetTransform()->SetLocalPosition({ 340.0f, -45.0f, 0.0f });
	cam1BScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam1BScreenRenderer_->Off();

	cam1BRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1BRenderer_->SetImage("cam1B.png", true);
	cam1BRenderer_->GetTransform()->SetLocalPosition({ 340.0f, -45.0f, 0.0f });
	cam1BRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam1BRenderer_->Off();

	cam1CScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1CScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam1CScreenRenderer_->GetTransform()->SetLocalPosition({ 300.0f, -120.0f, 0.0f });
	cam1CScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam1CScreenRenderer_->Off();

	cam1CRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam1CRenderer_->SetImage("cam1C.png", true);
	cam1CRenderer_->GetTransform()->SetLocalPosition({ 300.0f, -120.0f, 0.0f });
	cam1CRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam1CRenderer_->Off();

	cam5ScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam5ScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam5ScreenRenderer_->GetTransform()->SetLocalPosition({ 230.0f, -75.0f, 0.0f });
	cam5ScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam5ScreenRenderer_->Off();

	cam5Renderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam5Renderer_->SetImage("cam5.png", true);
	cam5Renderer_->GetTransform()->SetLocalPosition({ 230.0f, -75.0f, 0.0f });
	cam5Renderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam5Renderer_->Off();

	cam3ScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam3ScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam3ScreenRenderer_->GetTransform()->SetLocalPosition({ 270.0f, -220.0f, 0.0f });
	cam3ScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam3ScreenRenderer_->Off();

	cam3Renderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam3Renderer_->SetImage("cam3.png", true);
	cam3Renderer_->GetTransform()->SetLocalPosition({ 270.0f, -220.0f, 0.0f });
	cam3Renderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam3Renderer_->Off();

	cam2AScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam2AScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam2AScreenRenderer_->GetTransform()->SetLocalPosition({ 355.0f, -235.0f, 0.0f });
	cam2AScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam2AScreenRenderer_->Off();

	cam2ARenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam2ARenderer_->SetImage("cam2A.png", true);
	cam2ARenderer_->GetTransform()->SetLocalPosition({ 355.0f, -235.0f, 0.0f });
	cam2ARenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam2ARenderer_->Off();

	cam2BScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam2BScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam2BScreenRenderer_->GetTransform()->SetLocalPosition({ 355.0f, -278.0f, 0.0f });
	cam2BScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam2BScreenRenderer_->Off();

	cam2BRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam2BRenderer_->SetImage("cam2B.png", true);
	cam2BRenderer_->GetTransform()->SetLocalPosition({ 355.0f, -278.0f, 0.0f });
	cam2BRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam2BRenderer_->Off();

	cam7ScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam7ScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam7ScreenRenderer_->GetTransform()->SetLocalPosition({ 567.0f, -75.0f, 0.0f });
	cam7ScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam7ScreenRenderer_->Off();

	cam7Renderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam7Renderer_->SetImage("cam7.png", true);
	cam7Renderer_->GetTransform()->SetLocalPosition({ 567.0f, -75.0f, 0.0f });
	cam7Renderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam7Renderer_->Off();

	cam6ScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam6ScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam6ScreenRenderer_->GetTransform()->SetLocalPosition({ 562.0f, -205.0f, 0.0f });
	cam6ScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam6ScreenRenderer_->Off();

	cam6Renderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam6Renderer_->SetImage("cam6.png", true);
	cam6Renderer_->GetTransform()->SetLocalPosition({ 562.0f, -205.0f, 0.0f });
	cam6Renderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam6Renderer_->Off();

	cam4AScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam4AScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam4AScreenRenderer_->GetTransform()->SetLocalPosition({ 463.0f, -235.0f, 0.0f });
	cam4AScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam4AScreenRenderer_->Off();

	cam4ARenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam4ARenderer_->SetImage("cam2A.png", true);
	cam4ARenderer_->GetTransform()->SetLocalPosition({ 463.0f, -235.0f, 0.0f });
	cam4ARenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam4ARenderer_->Off();

	cam4BScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam4BScreenRenderer_->SetImage("CamScreenOff.png", true);
	cam4BScreenRenderer_->GetTransform()->SetLocalPosition({ 463.0f, -278.0f, 0.0f });
	cam4BScreenRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI1));
	//cam4BScreenRenderer_->Off();

	cam4BRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	cam4BRenderer_->SetImage("cam2B.png", true);
	cam4BRenderer_->GetTransform()->SetLocalPosition({ 463.0f, -278.0f, 0.0f });
	cam4BRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::UI2));
	//cam4BRenderer_->Off();

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
		muteCallCollision_->GetTransform()->SetLocalScaling(muteCallRenderer_->GetTransform()->GetLocalScaling());
		muteCallCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		cam1ACollision_ = CreateTransformComponent<GameEngineCollision>();
		cam1ACollision_->GetTransform()->SetLocalPosition(cam1AScreenRenderer_->GetTransform()->GetLocalPosition());
		cam1ACollision_->GetTransform()->SetLocalScaling(cam1AScreenRenderer_->GetTransform()->GetLocalScaling());
		cam1ACollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam1BCollision_ = CreateTransformComponent<GameEngineCollision>();
		cam1BCollision_->GetTransform()->SetLocalPosition(cam1BScreenRenderer_->GetTransform()->GetLocalPosition());
		cam1BCollision_->GetTransform()->SetLocalScaling(cam1BScreenRenderer_->GetTransform()->GetLocalScaling());
		cam1BCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam1CCollision_ = CreateTransformComponent<GameEngineCollision>();
		cam1CCollision_->GetTransform()->SetLocalPosition(cam1CScreenRenderer_->GetTransform()->GetLocalPosition());
		cam1CCollision_->GetTransform()->SetLocalScaling(cam1CScreenRenderer_->GetTransform()->GetLocalScaling());
		cam1CCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam5Collision_ = CreateTransformComponent<GameEngineCollision>();
		cam5Collision_->GetTransform()->SetLocalPosition(cam5ScreenRenderer_->GetTransform()->GetLocalPosition());
		cam5Collision_->GetTransform()->SetLocalScaling(cam5ScreenRenderer_->GetTransform()->GetLocalScaling());
		cam5Collision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam3Collision_ = CreateTransformComponent<GameEngineCollision>();
		cam3Collision_->GetTransform()->SetLocalPosition(cam3ScreenRenderer_->GetTransform()->GetLocalPosition());
		cam3Collision_->GetTransform()->SetLocalScaling(cam3ScreenRenderer_->GetTransform()->GetLocalScaling());
		cam3Collision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam2ACollision_ = CreateTransformComponent<GameEngineCollision>();
		cam2ACollision_->GetTransform()->SetLocalPosition(cam2AScreenRenderer_->GetTransform()->GetLocalPosition());
		cam2ACollision_->GetTransform()->SetLocalScaling(cam2AScreenRenderer_->GetTransform()->GetLocalScaling());
		cam2ACollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam2BCollision_ = CreateTransformComponent<GameEngineCollision>();
		cam2BCollision_->GetTransform()->SetLocalPosition(cam2BScreenRenderer_->GetTransform()->GetLocalPosition());
		cam2BCollision_->GetTransform()->SetLocalScaling(cam2BScreenRenderer_->GetTransform()->GetLocalScaling());
		cam2BCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam7Collision_ = CreateTransformComponent<GameEngineCollision>();
		cam7Collision_->GetTransform()->SetLocalPosition(cam7ScreenRenderer_->GetTransform()->GetLocalPosition());
		cam7Collision_->GetTransform()->SetLocalScaling(cam7ScreenRenderer_->GetTransform()->GetLocalScaling());
		cam7Collision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	
		cam6Collision_ = CreateTransformComponent<GameEngineCollision>();
		cam6Collision_->GetTransform()->SetLocalPosition(cam6ScreenRenderer_->GetTransform()->GetLocalPosition());
		cam6Collision_->GetTransform()->SetLocalScaling(cam6ScreenRenderer_->GetTransform()->GetLocalScaling());
		cam6Collision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));

		cam4ACollision_ = CreateTransformComponent<GameEngineCollision>();
		cam4ACollision_->GetTransform()->SetLocalPosition(cam4AScreenRenderer_->GetTransform()->GetLocalPosition());
		cam4ACollision_->GetTransform()->SetLocalScaling(cam4AScreenRenderer_->GetTransform()->GetLocalScaling());
		cam4ACollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	
		cam4BCollision_ = CreateTransformComponent<GameEngineCollision>();
		cam4BCollision_->GetTransform()->SetLocalPosition(cam4BScreenRenderer_->GetTransform()->GetLocalPosition());
		cam4BCollision_->GetTransform()->SetLocalScaling(cam4BScreenRenderer_->GetTransform()->GetLocalScaling());
		cam4BCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
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
	GetLevel()->PushDebugRender(cam1ACollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam1BCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam1CCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam5Collision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam3Collision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam2ACollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam2BCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam7Collision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam6Collision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam4ACollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(cam4BCollision_->GetTransform(), CollisionType::Rect);
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