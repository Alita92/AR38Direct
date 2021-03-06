#include "PreCompile.h"
#include "GameMouse.h"
#include "ENUM.h"

#include <GameEngine/GameEngineCollision.h>

GameMouse::GameMouse() // default constructer 디폴트 생성자
	: mouseCollision_(nullptr)
{

}

GameMouse::~GameMouse() // default destructer 디폴트 소멸자
{

}

void GameMouse::ImageInit()
{
	UIRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	//SetCurSor("MousePointer_Sampling.png");
}

void GameMouse::CollisionInit()
{
	mouseCollision_ = CreateTransformComponent<GameEngineCollision>();
	mouseCollision_->GetTransform()->SetLocalPosition(float4{ 0.0f, 0.0f, 1.0f });
	mouseCollision_->GetTransform()->SetLocalScaling(float4{ 3.0f, 3.0f, 1.0f });
	mouseCollision_->SetCollisionGroup(static_cast<int>(InGameCollisonType::MOUSEPOINTER));
}

void GameMouse::Start()
{
	ImageInit();
	CollisionInit();
}

void GameMouse::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
}

