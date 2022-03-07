#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "ENUM.h"

OfficeTest::OfficeTest() // default constructer ����Ʈ ������
	: MainRenderer_(nullptr), LdoorRenderer_(nullptr), RdoorRenderer_(nullptr), FanRenderer_(nullptr)
{

}

OfficeTest::~OfficeTest() // default destructer ����Ʈ �Ҹ���
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
		// �������ɾ� ����� ��
		MainRenderer_->SetRenderGroup(static_cast<int>(RenderOrder::MAX));
		MainRenderer_->SetChangeAnimation("JumpScareFreddy", true);
		// ���� �ִϸ��̼��� ������� �������� ������� ����..
	}
}

void OfficeTest::InitAnimation()
{
	{
		MainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::BACKGROUND0));
		MainRenderer_->SetImage("OfficeBasic.png", true);

		MainRenderer_->CreateAnimationFolder("JumpScareBonnie", "JumpScareBonnie", 0.04f, false);
		MainRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f, false);
		MainRenderer_->CreateAnimationFolder("JumpScareFreddy", "JumpScareFreddy", 0.04f, false);
	}

	{
		LdoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		LdoorRenderer_->SetImage("LdoorStatic.png", true);
		LdoorRenderer_->GetTransform()->SetLocalPosition({-550.0f, 0.0f, 1.0f});
		LdoorRenderer_->CreateAnimationFolder("LdoorClose","LdoorClose", 0.04f, false);
		LdoorRenderer_->CreateAnimationFolder("LdoorOpen", "LdoorOpen", 0.04f, false);
	}

	{
		RdoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		RdoorRenderer_->SetImage("RdoorStatic.png", true);
		RdoorRenderer_->GetTransform()->SetLocalPosition({ 550.0f, 0.0f, 1.0f });
		RdoorRenderer_->CreateAnimationFolder("RdoorClose", "RdoorClose", 0.04f, false);
		RdoorRenderer_->CreateAnimationFolder("RdoorOpen", "RdoorOpen", 0.04f, false);
	}

	{
		FanRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform(), static_cast<int>(RenderOrder::OBJECT0));
		FanRenderer_->SetImage("OfficeFanDefault.png", true);
		FanRenderer_->GetTransform()->SetLocalPosition({49.0f, -41.0f, 1.0f});
		FanRenderer_->CreateAnimationFolder("OfficeFan", "OfficeFan", 0.02f);
		FanRenderer_->SetChangeAnimation("OfficeFan");
	}
	

}