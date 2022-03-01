#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleFreddy.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::ResourceInit()
{
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("Title");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory soundDir;
		soundDir.MoveParent("AR38Direct");
		soundDir.MoveChild("Resources");
		soundDir.MoveChild("Sound");
		soundDir.MoveChild("Title");
	}
}

void TitleLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// 타이틀 배경화면의 프레디 애니메이션 액터입니다.
		TitleFreddy* titleFreddy = CreateActor<TitleFreddy>();
	
	}
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{

}
void TitleLevel::LevelChangeEndEvent()
{

}
void TitleLevel::LevelChangeStartEvent()
{
	ResourceInit();

}
