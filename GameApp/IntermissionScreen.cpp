#include "PreCompile.h"
#include "IntermissionScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "ENUM.h"

IntermissionScreen::IntermissionScreen() // default constructer 디폴트 생성자
	: mainRenderer_(nullptr), typoRenderer_(nullptr)
{

}

IntermissionScreen::~IntermissionScreen() // default destructer 디폴트 소멸자
{

}


void IntermissionScreen::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });

	mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	mainRenderer_->SetImage("ClearScreen.png", true);
	mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<float>(RenderOrder::BACKGROUND1) });

	typoRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	typoRenderer_->SetImage("Day1.png", true);
	typoRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<float>(RenderOrder::OBJECT1) });
}

void IntermissionScreen::Update(float _DeltaTime)
{

}