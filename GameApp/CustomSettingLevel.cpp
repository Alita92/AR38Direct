#include "PreCompile.h"
#include "CustomSettingLevel.h"

#include <GameEngine/GameEngineCore.h>

#include "CustomSettingController.h"
#include "GameMouse.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

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
	controller_ = CreateActor<CustomSettingController>();
}

void CustomSettingLevel::LevelUpdate(float _DeltaTime)
{
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

