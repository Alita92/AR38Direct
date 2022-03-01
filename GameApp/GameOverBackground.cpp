#include "PreCompile.h"
#include "GameOverBackground.h"

#include <GameEngine/GameEngineImageRenderer.h>

GameOverBackground::GameOverBackground() // default constructer 디폴트 생성자
	: gameOverBackgroundRenderer_(nullptr), gameOverTextRenderer_(nullptr)
{

}

GameOverBackground::~GameOverBackground() // default destructer 디폴트 소멸자
{

}

void GameOverBackground::Start()
{

}

void GameOverBackground::Update(float _Deltatime)
{
	gameOverBackgroundRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	gameOverBackgroundRenderer_->SetImage("GameOverBackground.png", true);

	gameOverTextRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	gameOverTextRenderer_->SetImage("GameOverText.png", true);
	gameOverTextRenderer_->GetTransform()->SetLocalPosition({ 500.0f, -300.0f, 1.0f });
}

