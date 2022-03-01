#include "PreCompile.h"
#include "GameOverLevel.h"

// Actor
#include "GameOverBackground.h"

GameOverLevel::GameOverLevel() // default constructer 디폴트 생성자
{

}

GameOverLevel::~GameOverLevel() // default destructer 디폴트 소멸자
{

}

GameOverLevel::GameOverLevel(GameOverLevel&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameOverLevel::ResourceInit()
{
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("GameOver");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}

	{
		//GameEngineDirectory soundDir;
		//soundDir.MoveParent("AR38Direct");
		//soundDir.MoveChild("Resources");
		//soundDir.MoveChild("Sound");
		//soundDir.MoveChild("GameOver");
	}
}
void GameOverLevel::LevelStart()
{
	ResourceInit();

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// 게임오버 배경화면과 텍스트 액터입니다.
		GameOverBackground* gameOverBackground = CreateActor<GameOverBackground>();
	}
}
void GameOverLevel::LevelUpdate(float _DeltaTime)
{

}
void GameOverLevel::LevelChangeEndEvent()
{

}
void GameOverLevel::LevelChangeStartEvent()
{

}