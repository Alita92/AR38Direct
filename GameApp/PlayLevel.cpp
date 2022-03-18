#include "PreCompile.h"
#include "PlayLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>

#include "OfficeTest.h"
#include "OfficeFan.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::ResourceInit()
{
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("Play"); 
		
		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
		
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareBonnie"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareChica"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFreddy"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("OfficeFan"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("LdoorClose"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("LdoorOpen"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorClose"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorOpen"));

	}
}

void PlayLevel::LevelStart()
{
	ResourceInit();

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		OfficeTest* officeTest = CreateActor<OfficeTest>();
	}

	{
		OfficeFan* officeFan = CreateActor<OfficeFan>();
	}
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{

}
void PlayLevel::LevelChangeEndEvent()
{

}
void PlayLevel::LevelChangeStartEvent()
{

}
