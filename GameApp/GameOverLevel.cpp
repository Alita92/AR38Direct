#include "PreCompile.h"
#include "GameOverLevel.h"

// Actor
#include "GameOverController.h"

GameOverLevel::GameOverLevel() // default constructer ����Ʈ ������
	: controller_(nullptr)
{

}

GameOverLevel::~GameOverLevel() // default destructer ����Ʈ �Ҹ���
{

}

void GameOverLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	controller_ = CreateActor<GameOverController>();
}

void GameOverLevel::LevelUpdate(float _DeltaTime)
{

}
void GameOverLevel::LevelChangeEndEvent()
{
	controller_->Reloading();
}
void GameOverLevel::LevelChangeStartEvent()
{

}