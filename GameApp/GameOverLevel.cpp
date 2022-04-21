#include "PreCompile.h"
#include "GameOverLevel.h"

// Actor
#include "GameOverController.h"
#include "UserGame.h"

GameOverLevel::GameOverLevel() // default constructer 디폴트 생성자
	: controller_(nullptr)
{

}

GameOverLevel::~GameOverLevel() // default destructer 디폴트 소멸자
{

}

void GameOverLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));


}

void GameOverLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		controller_ = CreateActor<GameOverController>();
		CreateActorCheck = true;
	}
}
void GameOverLevel::LevelChangeEndEvent()
{
	controller_->Reloading();
}
void GameOverLevel::LevelChangeStartEvent()
{

}