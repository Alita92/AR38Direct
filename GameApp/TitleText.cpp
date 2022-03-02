#include "PreCompile.h"
#include "TitleText.h"

#include <GameEngine/GameEngineImageRenderer.h>

TitleText::TitleText() // default constructer 디폴트 생성자
	: titleName_(nullptr), titleScott_(nullptr), titleNewGame_(nullptr), titleContinue_(nullptr)
{

}

TitleText::~TitleText() // default destructer 디폴트 소멸자
{

}

void TitleText::Start()
{
	titleName_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleName_->SetImage("TitleName.png", true);
	titleName_->GetTransform()->SetLocalPosition({ -500.0f, 200.0f, 1.0f });
	titleName_->SetOrder(10);

	titleScott_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleScott_->SetImage("TitleScott.png", true);
	titleScott_->GetTransform()->SetLocalPosition({ 500.0f, -330.0f, 1.0f });
	titleScott_->SetOrder(10);

	titleContinue_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleContinue_->SetImage("TitleContinue.png", true);
	titleContinue_->GetTransform()->SetLocalPosition({ -500.0f, -130.0f, 1.0f });
	titleContinue_->SetOrder(10);

	titleNewGame_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleNewGame_->SetImage("TitleNewGame.png", true);
	titleNewGame_->GetTransform()->SetLocalPosition({ -500.0f, -60.0f, 1.0f });
	titleNewGame_->SetOrder(10);
}


void TitleText::Update(float _Deltatime)
{

}