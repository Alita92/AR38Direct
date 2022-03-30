#include "PreCompile.h"
#include "ENUM.h"
#include "TitleText.h"
#include "TitleLevel.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

TitleText::TitleText() // default constructer 디폴트 생성자
	: titleName_(nullptr), titleScott_(nullptr), titleNewGame_(nullptr), titleContinue_(nullptr), titleNewGameCollision_(nullptr), titleContinueCollision_(nullptr), titleArrow_(nullptr)
{

}

TitleText::~TitleText() // default destructer 디폴트 소멸자
{

}

void TitleText::ImageInit()
{
	titleName_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleName_->SetImage("TitleName.png", true);
	titleName_->GetTransform()->SetLocalPosition({ -370.0f, 200.0f, static_cast<float>(RenderOrder::OBJECT0)});

	titleScott_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleScott_->SetImage("TitleScott.png", true);
	titleScott_->GetTransform()->SetLocalPosition({ 500.0f, -330.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	titleArrow_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleArrow_->SetImage("TItleArrow.png", true);
	titleArrow_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<float>(RenderOrder::OBJECT0) });
	titleArrow_->Off();

	titleNewGame_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleNewGame_->SetImage("TitleNewGame.png", true);
	titleNewGame_->GetTransform()->SetLocalPosition({ -370.0f, -60.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	titleContinue_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleContinue_->SetImage("TitleContinue.png", true);
	titleContinue_->GetTransform()->SetLocalPosition({ -370.0f, -130.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	title6thNight_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	title6thNight_->SetImage("Title6thNight.png", true);
	title6thNight_->GetTransform()->SetLocalPosition({ -360.0f, -210.0f,  static_cast<float>(RenderOrder::OBJECT0) });

	titleCustomNight_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleCustomNight_->SetImage("TitleCustomNight.png", true);
	titleCustomNight_->GetTransform()->SetLocalPosition({-320.0f, -280.0f, static_cast<float>(RenderOrder::OBJECT0) });
}

void TitleText::CollisionInit()
{
	{
		titleNewGameCollision_ = CreateTransformComponent<GameEngineCollision>();
		titleNewGameCollision_->GetTransform()->SetLocalPosition(titleNewGame_->GetTransform()->GetLocalPosition());
		titleNewGameCollision_->GetTransform()->SetLocalScaling(titleNewGame_->GetTransform()->GetLocalScaling());
		titleNewGameCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		titleContinueCollision_ = CreateTransformComponent<GameEngineCollision>();
		titleContinueCollision_->GetTransform()->SetLocalPosition(titleContinue_->GetTransform()->GetLocalPosition());
		titleContinueCollision_->GetTransform()->SetLocalScaling(titleContinue_->GetTransform()->GetLocalScaling());
		titleContinueCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		title6thNightCollision_ = CreateTransformComponent<GameEngineCollision>();
		title6thNightCollision_->GetTransform()->SetLocalPosition(title6thNight_->GetTransform()->GetLocalPosition());
		title6thNightCollision_->GetTransform()->SetLocalScaling(title6thNight_->GetTransform()->GetLocalScaling());
		title6thNightCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

	{
		titleCustomNightCollision_ = CreateTransformComponent<GameEngineCollision>();
		titleCustomNightCollision_->GetTransform()->SetLocalPosition(titleCustomNight_->GetTransform()->GetLocalPosition());
		titleCustomNightCollision_->GetTransform()->SetLocalScaling(titleCustomNight_->GetTransform()->GetLocalScaling());
		titleCustomNightCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::UI));
	}

}

void TitleText::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });

	ImageInit();
	CollisionInit();
}


void TitleText::Update(float _Deltatime)
{
	DebugRenderUpdate();
}



void TitleText::DebugRenderUpdate()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(titleNewGameCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(titleContinueCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(titleCustomNightCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(title6thNightCollision_->GetTransform(), CollisionType::Rect);
#endif
}


