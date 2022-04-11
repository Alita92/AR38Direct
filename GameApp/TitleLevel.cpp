#include "PreCompile.h"
#include "TitleLevel.h"

#include "GameMouse.h"
#include "TitleFreddy.h"

#include "TitleText.h"
#include "TitleNewsPaper.h"

#include "TitleController.h"
#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineCore.h>

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
	GetMainCamera()->SetProjectionMode(ProjectionMode::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -300.0f));

	if (nullptr == titleController_)
	{
		titleController_ = CreateActor<TitleController>();
	}
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
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