#include "PreCompile.h"
#include "TitleLevel.h"

#include "GameMouse.h"
#include "TitleFreddy.h"

#include "TitleText.h"



#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineCore.h>


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// Ÿ��Ʋ���� ���콺 �����Դϴ�.
		GameMouse* mouseActor = CreateActor<GameMouse>();
		mouseActor->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	}

	{
		// Ÿ��Ʋ ���ȭ���� ������ �ִϸ��̼� �����Դϴ�.
		TitleFreddy* titleFreddy = CreateActor<TitleFreddy>();
		// �޴� �ؽ�Ʈ�� �����Դϴ�.
		TitleText* titleText = CreateActor<TitleText>();
	}
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIP"))
	{
		GameEngineCore::LevelChange("Play");
	}

	if (true == GameEngineInput::GetInst().Down("ESC"))
	{

	}
}
void TitleLevel::LevelChangeEndEvent()
{

}
void TitleLevel::LevelChangeStartEvent()
{

}