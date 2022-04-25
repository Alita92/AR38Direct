#include "PreCompile.h"
#include "IntermissionLevel.h"

#include "IntermissionController.h"

#include "FadeScreen.h"
#include "UserGame.h"

IntermissionLevel::IntermissionLevel() // default constructer ����Ʈ ������
	: intermissionController_(nullptr)
{

}

IntermissionLevel::~IntermissionLevel() // default destructer ����Ʈ �Ҹ���
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

