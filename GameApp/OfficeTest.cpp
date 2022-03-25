#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "ENUM.h"

OfficeTest::OfficeTest() // default constructer 디폴트 생성자
	: mainRenderer_(nullptr), lDoorRenderer_(nullptr), rDoorRenderer_(nullptr), isLdoorClosed_(false), isRdoorClosed_(false)
{
}

OfficeTest::~OfficeTest() // default destructer 디폴트 소멸자
{

}


void OfficeTest::Start()
{
	GetTransform()->SetWorldPosition({0.0f ,0.0f, 10.0f});

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
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f, -50.0f });
		mainRenderer_->SetChangeAnimation("JumpScareBonnie");
		// 폴더 애니메이션이 순서대로 프레임이 재생되질 않음..
	}

	if (true == GameEngineInput::GetInst().Down("LDoor_Toggle"))
	{
		if (false == isLdoorClosed_)
		{
			lDoorRenderer_->SetChangeAnimation("LdoorClose");
			isLdoorClosed_ = true;
		}
		else
		{

			lDoorRenderer_->SetChangeAnimation("LdoorOpen");
			isLdoorClosed_ = false;
		}
	}

	if (true == GameEngineInput::GetInst().Down("RDoor_Toggle"))
	{
		if (false == isRdoorClosed_)
		{
			rDoorRenderer_->SetChangeAnimation("RdoorClose");
			isRdoorClosed_ = true;
		}
		else
		{
			rDoorRenderer_->SetChangeAnimation("RdoorOpen");
			isRdoorClosed_ = false;
		}
	}
}

void OfficeTest::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		mainRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
	}

	{
		lDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		lDoorRenderer_->SetImage("LdoorStatic.png", true);
		lDoorRenderer_->GetTransform()->SetLocalPosition({-550.0f, 0.0f, -1.0f});
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png","LdoorClose", 14, 0 , 0.04f, false);
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorOpen", 0, 14, 0.04f, false);
	}

	{
		rDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 550.0f, 0.0f, -1.0f });
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorClose", 14, 0, 0.04f, false);
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorOpen", 0, 14, 0.04f, false);
	}
}