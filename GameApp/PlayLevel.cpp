#include "PreCompile.h"
#include "PlayLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include "GameMouse.h"

#include "GameController.h"
#include "UIController.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		GameController* gameController = CreateActor<GameController>();
	}

	{
		// 타이틀씬의 마우스 액터입니다.
		GameMouse* mouseActor = CreateActor<GameMouse>();
		mouseActor->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	}
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
