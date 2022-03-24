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
		// 타이틀씬의 마우스 액터입니다.
		GameMouse* mouseActor = CreateActor<GameMouse>();
		mouseActor->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	}

	{
		// 타이틀 배경화면의 프레디 애니메이션 액터입니다.
		TitleFreddy* titleFreddy = CreateActor<TitleFreddy>();
		// 메뉴 텍스트들 액터입니다.
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