#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>

OfficeTest::OfficeTest() // default constructer ����Ʈ ������
{

}

OfficeTest::~OfficeTest() // default destructer ����Ʈ �Ҹ���
{

}

OfficeTest::OfficeTest(OfficeTest&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void OfficeTest::Start()
{
	ImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	ImageRenderer_->SetImage("1.png", true);
	//ImageRenderer_->SetIndex(10);
	ImageRenderer_->CreateAnimationFolder("JumpScareBonnie", "JumpScareBonnie", 0.04f);
	ImageRenderer_->CreateAnimationFolder("JumpScareChica", "JumpScareChica", 0.04f);
	ImageRenderer_->SetChangeAnimation("JumpScareBonnie");

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P'); 
	}
}

void OfficeTest::Update(float _Deltatime)
{

	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIPSCENE"))
	{
		ImageRenderer_->SetChangeAnimation("JumpScareChica");
	}
}