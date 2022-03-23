#include "PreCompile.h"
#include "CustomSettingLevel.h"

#include "CustomSettingUI.h"
#include "GameMouse.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

CustomSettingLevel::CustomSettingLevel() // default constructer 디폴트 생성자
{

}

CustomSettingLevel::~CustomSettingLevel() // default destructer 디폴트 소멸자
{

}

void CustomSettingLevel::ResourceInit()
{
	GameEngineDirectory imageDir;
	imageDir.MoveParent("AR38Direct");
	imageDir.MoveChild("Resources");
	imageDir.MoveChild("Image");
	imageDir.MoveChild("CustomSetting");

	std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

	for (size_t i = 0; i < allFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
	}
}

void CustomSettingLevel::LevelStart()
{
	ResourceInit();

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// 타이틀씬의 마우스 액터입니다.
		GameMouse* mouseActor = CreateActor<GameMouse>();
		mouseActor->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	}

	{
		CustomSettingUI* customSettingUI = CreateActor<CustomSettingUI>();
	}

}

void CustomSettingLevel::LevelUpdate(float _DeltaTime)
{

}

void CustomSettingLevel::LevelChangeEndEvent()
{

}

void CustomSettingLevel::LevelChangeStartEvent()
{

}

