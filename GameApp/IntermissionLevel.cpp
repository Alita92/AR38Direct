#include "PreCompile.h"
#include "IntermissionLevel.h"

#include "IntermissionController.h"

#include "FadeScreen.h"
#include "UserGame.h"

IntermissionLevel::IntermissionLevel() // default constructer 디폴트 생성자
	: intermissionController_(nullptr)
{

}

IntermissionLevel::~IntermissionLevel() // default destructer 디폴트 소멸자
{

}


void IntermissionLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));


	
}

void IntermissionLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{
		Sleep(10);
		intermissionController_ = CreateActor<IntermissionController>();
		CreateActorCheck = true;
	}
}

void IntermissionLevel::LevelChangeEndEvent()
{
	if (nullptr != intermissionController_)
	{
		intermissionController_->ControllerReloading();
	}
}

void IntermissionLevel::LevelChangeStartEvent()
{


}

