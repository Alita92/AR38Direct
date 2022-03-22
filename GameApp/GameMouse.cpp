#include "PreCompile.h"
#include "GameMouse.h"

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
	SetCurSor("MousePointer_Sampling.png");
}

void GameMouse::CollisionInit()
{
	mouseCollision_ = CreateTransformComponent<GameEngineCollision>();
	mouseCollision_->GetTransform()->SetLocalScaling(float4{ 12.0f, 19.0f, 1.0f });
	mouseCollision_->SetCollisionGroup(1);
}

void GameMouse::Start()
{
	ImageInit();
	CollisionInit();
}

void GameMouse::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());

#ifdef _DEBUG
	GetLevel()->PushDebugRender(mouseCollision_->GetTransform(), CollisionType::Rect);
#endif
}

