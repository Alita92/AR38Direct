#include "PreCompile.h"
#include "TitleLevel.h"

#include "GameMouse.h"
#include "TitleFreddy.h"

#include "TitleText.h"



#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineCore.h>


TitleLevel::TitleLevel()
	: isUIButtonDown_(false), nextLevel_(Level::MAX)
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
		//GameEngineDirectory soundDir;
		//soundDir.MoveParent("AR38Direct");
		//soundDir.MoveChild("Resources");
		//soundDir.MoveChild("Sound");
		//soundDir.MoveChild("Title");
	}
}

void TitleLevel::LevelStart()
{
	ResourceInit();

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// Ÿ��Ʋ���� ���콺 �����Դϴ�.
		GameMouse* mouseActor = CreateActor<GameMouse>();
		mouseActor->GetUIRenderer()->SetRenderGroup(static_cast<int>(RenderOrder::UI0));
	}

	{
		// Ÿ��Ʋ ���ȭ���� ������ �ִϸ��̼� �����Դϴ�.
		TitleFreddy* titleFreddy = CreateActor<TitleFreddy>();
		// �޴� �ؽ�Ʈ�� �����Դϴ�.
		TitleText* titleText = CreateActor<TitleText>();
	}
}

void TitleLevel::LevelUpdate(float _DeltaTime)
{


	CheckLevelChangeRequest();

}
void TitleLevel::LevelChangeEndEvent()
{

}
void TitleLevel::LevelChangeStartEvent()
{

}

void TitleLevel::CheckLevelChangeRequest()
{
	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIP"))
	{
		GameEngineCore::LevelChange("Play");
	}

	if (true == isUIButtonDown_)
	{

	}
}

void TitleLevel::SetNextLevel(Level _nextLevel)
{
	nextLevel_ = _nextLevel;
}
