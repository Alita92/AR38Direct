#include "PreCompile.h"
#include "MouseActor.h"
#include <GameEngine\GameEngineInput.h>

MouseActor::MouseActor()
	: UIRenderer(nullptr)
{
}

MouseActor::~MouseActor()
{
}


void MouseActor::SetCurSor(std::string _Name)
{
	UIRenderer->SetImage(_Name, true);
}

void MouseActor::SetCurSor(std::string _Name, int _Index)
{
	UIRenderer->SetImage(_Name);
	UIRenderer->SetIndex(_Index);
}

void MouseActor::Start()
{
	UIRenderer = CreateTransformComponent<GameEngineUIRenderer>();
	UIRenderer->GetTransform()->SetLocalScaling({ 50.0f, 50.0f });
	SetCurSor("MousePointer1.png");

}

void MouseActor::Update(float _DeltaTime)
{
	GetTransform()->SetWorldPosition(GameEngineInput::GetInst().GetMouse3DPos());
}