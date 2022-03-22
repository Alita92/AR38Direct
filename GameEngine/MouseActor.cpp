#include "PreCompile.h"
#include "MouseActor.h"

#include <GameEngine/GameEngineCollision.h>
#include <GameEngine\GameEngineInput.h>

MouseActor::MouseActor()
	: UIRenderer_(nullptr)
{
}

MouseActor::~MouseActor()
{
}


void MouseActor::SetCurSor(std::string _Name)
{
	UIRenderer_->SetImage(_Name, true);
}

void MouseActor::SetCurSor(std::string _Name, int _Index)
{
	UIRenderer_->SetImage(_Name);
	UIRenderer_->SetIndex(_Index);
}

void MouseActor::Start()
{
	UIRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
	UIRenderer_->GetTransform()->SetLocalScaling({ 50.0f, 50.0f });
	SetCurSor("MousePointer1.png");

}

void MouseActor::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());


}