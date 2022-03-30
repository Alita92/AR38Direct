#include "PreCompile.h"
#include "ENUM.h"
#include "TitleText.h"
#include "TitleLevel.h"
#include <GameEngine/GameEngineUIRenderer.h>
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
	titleName_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleName_->SetImage("TitleName.png", true);
	titleName_->GetTransform()->SetLocalPosition({ -370.0f, 200.0f, 0.0f });
	titleName_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));

	titleScott_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleScott_->SetImage("TitleScott.png", true);
	titleScott_->GetTransform()->SetLocalPosition({ 500.0f, -330.0f,0.0f });
	titleScott_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));

	titleArrow_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleArrow_->SetImage("TItleArrow.png", true);
	titleArrow_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,0.0f });
	titleArrow_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));
	titleArrow_->Off();

	titleNewGame_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleNewGame_->SetImage("TitleNewGame.png", true);
	titleNewGame_->GetTransform()->SetLocalPosition({ -370.0f, -60.0f,0.0f });
	titleNewGame_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));

	titleContinue_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleContinue_->SetImage("TitleContinue.png", true);
	titleContinue_->GetTransform()->SetLocalPosition({ -370.0f, -130.0f,  0.0f});
	titleContinue_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));

	title6thNight_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	title6thNight_->SetImage("Title6thNight.png", true);
	title6thNight_->GetTransform()->SetLocalPosition({ -360.0f, -210.0f, 0.0f });
	title6thNight_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));

	titleCustomNight_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	titleCustomNight_->SetImage("TitleCustomNight.png", true);
	titleCustomNight_->GetTransform()->SetLocalPosition({-320.0f, -280.0f,0.0f });
	titleCustomNight_->SetRenderGroup(static_cast<int>(UIRenderOrder::UI1));
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


