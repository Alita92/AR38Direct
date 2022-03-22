#include "PreCompile.h"
#include "ENUM.h"
#include "TitleText.h"
#include "TitleLevel.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageRenderer.h>

TitleText::TitleText() // default constructer 디폴트 생성자
	: titleName_(nullptr), titleScott_(nullptr), titleNewGame_(nullptr), titleContinue_(nullptr), titleNewGameCollision_(nullptr), titleContinueCollision_(nullptr)
{

}

TitleText::~TitleText() // default destructer 디폴트 소멸자
{

}

void TitleText::ImageInit()
{
	titleName_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleName_->SetImage("TitleName.png", true);
	titleName_->GetTransform()->SetLocalPosition({ -500.0f, 200.0f, 0.0f });
	//titleName_->SetOrder(10);

	titleScott_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleScott_->SetImage("TitleScott.png", true);
	titleScott_->GetTransform()->SetLocalPosition({ 500.0f, -330.0f, 0.0f });
	//	titleScott_->SetOrder(10);

	titleContinue_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleContinue_->SetImage("TitleContinue.png", true);
	titleContinue_->GetTransform()->SetLocalPosition({ -500.0f, -130.0f, 0.0f });
	//titleContinue_->SetOrder(10);

	titleNewGame_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleNewGame_->SetImage("TitleNewGame.png", true);
	titleNewGame_->GetTransform()->SetLocalPosition({ -500.0f, -60.0f, 0.0f });
	//titleNewGame_->SetOrder(10);
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

}

void TitleText::Start()
{
	GetTransform()->SetWorldPosition({ 0.f,0.f,0.f });

	ImageInit();
	CollisionInit();
}


void TitleText::Update(float _Deltatime)
{
	CollisionCheckUpdate();
	DebugRenderUpdate();
}

void TitleText::CollisionCheckUpdate()
{
	titleNewGameCollision_->Collision(
		CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleText::CollisionNewGame, this, std::placeholders::_1));

	titleContinueCollision_->Collision(
		CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&TitleText::CollisionContinue, this, std::placeholders::_1));
}


void TitleText::DebugRenderUpdate()
{
#ifdef _DEBUG
	GetLevel()->PushDebugRender(titleNewGameCollision_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushDebugRender(titleContinueCollision_->GetTransform(), CollisionType::Rect);
#endif
}

void TitleText::CollisionNewGame(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		GetLevel()->RequestLevelChange("Play");
	}
}

void TitleText::CollisionContinue(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Up("MOUSE_1"))
	{
		GetLevel()->RequestLevelChange("Play");
	}
}