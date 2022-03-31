#include "PreCompile.h"
#include "GameOverBackground.h"
#include "GlitchScreen.h"

#include "ENUM.h"

#include <GameEngine/GameEngineImageRenderer.h>

GameOverBackground::GameOverBackground() // default constructer 디폴트 생성자
	: gameOverBackgroundRenderer_(nullptr), gameOverTextRenderer_(nullptr), gameOverGlitchScreen_(nullptr)
{

}

GameOverBackground::~GameOverBackground() // default destructer 디폴트 소멸자
{

}

void GameOverBackground::InitImage()
{
	gameOverBackgroundRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	gameOverBackgroundRenderer_->SetImage("GameOverBackground.png", true);
	gameOverBackgroundRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::BACKGROUND1) });

	gameOverTextRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	gameOverTextRenderer_->SetImage("GameOverText.png", true);
	gameOverTextRenderer_->GetTransform()->SetLocalPosition({ 500.0f, -300.0f, static_cast<int>(RenderOrder::OBJECT1)});
}

void GameOverBackground::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	gameOverGlitchScreen_ = GetLevel()->CreateActor<GlitchScreen>();
	InitImage();
}

void GameOverBackground::Update(float _Deltatime)
{

}

void GameOverBackground::SetWhiteNoise(bool _on)
{
	gameOverGlitchScreen_->PlayAwakeScanLineFast();
	gameOverGlitchScreen_->PlayWhiteNoise(_on);
}

