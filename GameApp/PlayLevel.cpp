#include "PreCompile.h"
#include "PlayLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include "GameMouse.h"

#include "GameController.h"
#include "UIController.h"

PlayLevel::PlayLevel()
	: gameController_(nullptr)
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	if (nullptr == gameController_)
	{
		gameController_ = CreateActor<GameController>();
	}
	
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}
void PlayLevel::LevelChangeEndEvent()
{
	if (nullptr != gameController_)
	{
		gameController_->ControllerReloading();
	}

	gameController_->InitEnemyAILevel();
}
void PlayLevel::LevelChangeStartEvent()
{

}
