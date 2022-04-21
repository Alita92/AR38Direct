#include "PreCompile.h"
#include "TrialOverLevel.h"

#include "TrialOverController.h"
#include "UserGame.h"
TrialOverLevel::TrialOverLevel() // default constructer ����Ʈ ������
{

}

TrialOverLevel::~TrialOverLevel() // default destructer ����Ʈ �Ҹ���
{

}

void TrialOverLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	
}

void TrialOverLevel::LevelUpdate(float _DeltaTime)
{
	static bool CreateActorCheck = false;

	if (0 >= UserGame::LoadingFolder
		&& false == CreateActorCheck)
	{

		controller_ = CreateActor<TrialOverController>();
		CreateActorCheck = true;
	}
}
void TrialOverLevel::LevelChangeEndEvent()
{
	controller_->Reloading();
}
void TrialOverLevel::LevelChangeStartEvent()
{

}