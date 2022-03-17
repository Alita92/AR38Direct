#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "ENUM.h"

OfficeTest::OfficeTest() // default constructer 디폴트 생성자
	: mainRenderer_(nullptr), lDoorRenderer_(nullptr), rDoorRenderer_(nullptr), fanRenderer_(nullptr)
{

}

OfficeTest::~OfficeTest() // default destructer 디폴트 소멸자
{

}


void OfficeTest::Start()
{
	InitAnimation();

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P'); 
	}
}

void OfficeTest::Update(float _Deltatime)
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIPSCENE"))
	{
		// 점프스케어 디버깅 중
		mainRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::MAX));
		mainRenderer_->SetChangeAnimation("JumpScareFreddy", true);
		// 폴더 애니메이션이 순서대로 프레임이 재생되질 않음..
	}
}

void OfficeTest::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::BACKGROUND0));
		mainRenderer_->SetImage("OfficeBasic.png", true);
		
		mainRenderer_->CreateAnimationFolder("JumpScareBonnie", "JumpScareBonnie", 0.04f, false);
		mainRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f, false);
		mainRenderer_->CreateAnimationFolder("JumpScareFreddy", "JumpScareFreddy", 0.04f, false);
	}

	{
		lDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		lDoorRenderer_->SetImage("LdoorStatic.png", true);
		lDoorRenderer_->GetTransform()->SetLocalPosition({-550.0f, 0.0f, 1.0f});
		lDoorRenderer_->CreateAnimationFolder("LdoorClose","LdoorClose", 0.04f, false);
		lDoorRenderer_->CreateAnimationFolder("LdoorOpen", "LdoorOpen", 0.04f, false);
	}

	{
		rDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 550.0f, 0.0f, 1.0f });
		rDoorRenderer_->CreateAnimationFolder("RdoorClose", "RdoorClose", 0.04f, false);
		rDoorRenderer_->CreateAnimationFolder("RdoorOpen", "RdoorOpen", 0.04f, false);
	}

	{
		fanRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		fanRenderer_->SetImage("OfficeFanDefault.png", true);
		fanRenderer_->GetTransform()->SetLocalPosition({49.0f, -41.0f, 1.0f});
		fanRenderer_->CreateAnimationFolder("OfficeFan", "OfficeFan", 0.02f);
		fanRenderer_->SetChangeAnimation("OfficeFan");
	}
	

	//GetLevel()->PushDebugRender(GetTransform(), CollisionType::Rect);


}