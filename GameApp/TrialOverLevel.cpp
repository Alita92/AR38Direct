#include "PreCompile.h"
#include "TrialOverLevel.h"

#include "TrialOverController.h"

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

	controller_ = CreateActor<TrialOverController>();
}

void TrialOverLevel::LevelUpdate(float _DeltaTime)
{

}
void TrialOverLevel::LevelChangeEndEvent()
{
	controller_->Reloading();
}
void TrialOverLevel::LevelChangeStartEvent()
{

}