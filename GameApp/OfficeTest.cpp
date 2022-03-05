#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>

OfficeTest::OfficeTest() // default constructer 디폴트 생성자
	: MainRenderer_(nullptr), LdoorRenderer_(nullptr), RdoorRenderer_(nullptr), FanRenderer_(nullptr)
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
		LdoorRenderer_->SetChangeAnimation("LdoorClose", true);

		RdoorRenderer_->SetChangeAnimation("RdoorClose", true);
	}
}

void OfficeTest::InitAnimation()
{
	{
		MainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		MainRenderer_->SetImage("OfficeBasic.png", true);

		MainRenderer_->CreateAnimationFolder("JumpScareBonnie", "JumpScareBonnie", 0.04f, false);
		MainRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f, false);
		MainRenderer_->CreateAnimationFolder("JumpScareFreddy", "JumpScareFreddy", 0.04f, false);
	}

	{
		LdoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		LdoorRenderer_->SetImage("LdoorStatic.png", true);
		LdoorRenderer_->GetTransform()->SetLocalPosition({-500.0f, 0.0f, 1.0f});
		LdoorRenderer_->CreateAnimationFolder("LdoorClose","LdoorClose", 0.04f, false);
		LdoorRenderer_->CreateAnimationFolder("LdoorOpen", "LdoorOpen", 0.04f, false);
	}

	{
		RdoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		RdoorRenderer_->SetImage("RdoorStatic.png", true);
		RdoorRenderer_->GetTransform()->SetLocalPosition({ 500.0f, 0.0f, 1.0f });
		RdoorRenderer_->CreateAnimationFolder("RdoorClose", "RdoorClose", 0.04f, false);
		RdoorRenderer_->CreateAnimationFolder("RdoorOpen", "RdoorOpen", 0.04f, false);
	}

	{
		FanRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(20);
		FanRenderer_->SetImage("OfficeFanDefault.png", true);
		FanRenderer_->GetTransform()->SetLocalPosition({49.0f, -41.0f, 1.0f});
		FanRenderer_->CreateAnimationFolder("OfficeFan", "OfficeFan", 0.02f);
		FanRenderer_->SetChangeAnimation("OfficeFan");
	}
	

}