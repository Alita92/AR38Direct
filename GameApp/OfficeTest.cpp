#include "PreCompile.h"
#include "OfficeTest.h"
#include <GameEngine/GameEngineImageRenderer.h>

OfficeTest::OfficeTest() // default constructer 디폴트 생성자
{

}

OfficeTest::~OfficeTest() // default destructer 디폴트 소멸자
{

}

OfficeTest::OfficeTest(OfficeTest&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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