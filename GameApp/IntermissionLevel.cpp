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


void IntermissionLevel::ResourceInit()
{
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("Intermission");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}
}


void IntermissionLevel::LevelStart()
{
	ResourceInit();

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

