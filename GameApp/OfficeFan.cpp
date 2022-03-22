#include "PreCompile.h"
#include "OfficeFan.h"
#include <GameEngine/GameEngineImageRenderer.h>

OfficeFan::OfficeFan() // default constructer ����Ʈ ������
{

}

OfficeFan::~OfficeFan() // default destructer ����Ʈ �Ҹ���
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