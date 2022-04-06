#include "PreCompile.h"
#include "IntermissionLevel.h"

#include "IntermissionController.h"

#include "FadeScreen.h"

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

	if (nullptr == intermissionController_)
	{
		intermissionController_ = CreateActor<IntermissionController>();
	}
}

void IntermissionLevel::LevelUpdate(float _DeltaTime)
{

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

