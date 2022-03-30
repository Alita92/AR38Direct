#include "PreCompile.h"
#include "TitleNewsPaper.h"
#include "ENUM.h"

#include <GameEngine/GameEngineImageRenderer.h>

TitleNewsPaper::TitleNewsPaper() // default constructer 디폴트 생성자
	: newsPaperRenderer_(nullptr)
{

}

TitleNewsPaper::~TitleNewsPaper() // default destructer 디폴트 소멸자
{

}

void TitleNewsPaper::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 0.0f });

	newsPaperRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	newsPaperRenderer_->SetImage("TitlePrologue.png", true);
	newsPaperRenderer_->GetTransform()->SetLocalPosition({0.0f,0.0f,static_cast<float>(RenderOrder::BACKGROUND1)});
}

void TitleNewsPaper::Update(float _Deltatime)
{

}