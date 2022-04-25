#include "PreCompile.h"
#include "TitleLevel.h"

#include "GameMouse.h"
#include "TitleFreddy.h"

#include "TitleText.h"
#include "TitleNewsPaper.h"

#include "TitleController.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineCore.h>

#include "UserGame.h"
#include "GameStaticData.h"

TitleLevel::TitleLevel()
	: titleController_(nullptr)
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));


}

void TitleLevel::LevelUpdate(float _DeltaTime)
{

	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		Sleep(10);
		titleController_ = CreateActor<TitleController>();
		CreateActorCheck = true;
	}

	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIP"))
	{
		GameEngineCore::LevelChange("Play");
	}
}
void TitleLevel::LevelChangeEndEvent()
{
	if (nullptr != titleController_)
	{
		titleController_->ControllerReloading();
	}

}
void TitleLevel::LevelChangeStartEvent()
{

}