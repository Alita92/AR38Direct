#include "PreCompile.h"
#include "IntermissionLevel.h"

IntermissionLevel::IntermissionLevel() // default constructer ����Ʈ ������
{

}

IntermissionLevel::~IntermissionLevel() // default destructer ����Ʈ �Ҹ���
{

}

IntermissionLevel::IntermissionLevel(IntermissionLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}


void IntermissionLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{

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

