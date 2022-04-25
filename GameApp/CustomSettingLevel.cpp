#include "PreCompile.h"
#include "CustomSettingLevel.h"

#include <GameEngine/GameEngineCore.h>

#include "CustomSettingController.h"
#include "GameMouse.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "UserGame.h"

CustomSettingLevel::CustomSettingLevel() // default constructer 디폴트 생성자
	: controller_(nullptr)
{

}

CustomSettingLevel::~CustomSettingLevel() // default destructer 디폴트 소멸자
{

}

void CustomSettingLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));



}

void CustomSettingLevel::LevelUpdate(float _DeltaTime)
{

	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		Sleep(10);
		controller_ = CreateActor<CustomSettingController>();
		CreateActorCheck = true;
	}
	if (true == GameEngineInput::GetInst().Down("ESC"))
	{
		GameEngineCore::LevelChange("Title");
	}
}

void CustomSettingLevel::LevelChangeEndEvent()
{

}

void CustomSettingLevel::LevelChangeStartEvent()
{

}

