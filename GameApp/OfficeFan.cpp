#include "PreCompile.h"
#include "OfficeFan.h"
#include <GameEngine/GameEngineImageRenderer.h>

OfficeFan::OfficeFan() // default constructer 디폴트 생성자
{

}

OfficeFan::~OfficeFan() // default destructer 디폴트 소멸자
{

}

void OfficeFan::Start()
{
	GetTransform()->SetWorldPosition({49.0f, -41.0f, 0.0f});
	InitAnimation();
}

void OfficeFan::Update(float _Deltatime)
{

}

void OfficeFan::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeFanDefault.png", true);
		// mainRenderer_->GetTransform()->SetLocalPosition({ 49.0f, -41.0f, 0.0f });
		mainRenderer_->CreateAnimationFolder("OfficeFan", "OfficeFan", 0.02f);
		mainRenderer_->SetChangeAnimation("OfficeFan");
	}
}