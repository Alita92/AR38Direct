#include "PreCompile.h"
#include "WarningLevel.h"
#include "UserGame.h"
#include "ENUM.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "WarningController.h"
#include <GameEngine/GameEngineActor.h>
WarningLevel::WarningLevel() // default constructer 디폴트 생성자
	: controller_(nullptr)
{

}

WarningLevel::~WarningLevel() // default destructer 디폴트 소멸자
{

}

void WarningLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));


}

void WarningLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		Sleep(10);
		controller_ = CreateActor<WarningController>();
		CreateActorCheck = true;
	}
}
void WarningLevel::LevelChangeEndEvent()
{
	controller_->Reloading();
}
void WarningLevel::LevelChangeStartEvent()
{

}