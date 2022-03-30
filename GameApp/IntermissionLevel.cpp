#include "PreCompile.h"
#include "IntermissionLevel.h"

#include "IntermissionController.h"

IntermissionLevel::IntermissionLevel() // default constructer 디폴트 생성자
{

}

IntermissionLevel::~IntermissionLevel() // default destructer 디폴트 소멸자
{

}

IntermissionLevel::IntermissionLevel(IntermissionLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}


void IntermissionLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		IntermissionController* intermissionController = CreateActor<IntermissionController>();
	}
}

void IntermissionLevel::LevelUpdate(float _DeltaTime)
{

}

void IntermissionLevel::LevelChangeEndEvent()
{

}

void IntermissionLevel::LevelChangeStartEvent()
{

}

