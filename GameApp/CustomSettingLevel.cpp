#include "PreCompile.h"
#include "CustomSettingLevel.h"

#include "CustomSettingUI.h"
#include "GameMouse.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

CustomSettingLevel::CustomSettingLevel() // default constructer ����Ʈ ������
{

}

CustomSettingLevel::~CustomSettingLevel() // default destructer ����Ʈ �Ҹ���
{

}

void CustomSettingLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// Ÿ��Ʋ���� ���콺 �����Դϴ�.
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
