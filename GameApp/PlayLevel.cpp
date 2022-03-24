#include "PreCompile.h"
#include "PlayLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "OfficeTest.h"
#include "OfficeFan.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		OfficeTest* officeTest = CreateActor<OfficeTest>();
	}

	{
		OfficeFan* officeFan = CreateActor<OfficeFan>();
	}
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
