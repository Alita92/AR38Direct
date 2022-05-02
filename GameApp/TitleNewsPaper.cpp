#include "PreCompile.h"
#include "TitleNewsPaper.h"
#include "ENUM.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineBackgroundRenderer.h>

TitleNewsPaper::TitleNewsPaper() // default constructer ����Ʈ ������
	: newsPaperRenderer_(nullptr)
{

}

TitleNewsPaper::~TitleNewsPaper() // default destructer ����Ʈ �Ҹ���
{

}

void TitleNewsPaper::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f, 0.0f, 0.0f });

	newsPaperRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	newsPaperRenderer_->SetImage("TitlePrologueKR.png", true);
	newsPaperRenderer_->GetTransform()->SetLocalPosition({0.0f,0.0f,static_cast<float>(RenderOrder::BACKGROUND1)});
}

void TitleNewsPaper::Update(float _Deltatime)
{

}