#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine/EngineVertex.h>
#include "UserGame_Resources_Shader.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("AR38Direct");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}


	{
		// Title Level
		{
			GameEngineDirectory imageDir;
			imageDir.MoveParent("AR38Direct");
			imageDir.MoveChild("Resources");
			imageDir.MoveChild("Image");
			imageDir.MoveChild("Common");

			std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

			for (size_t i = 0; i < allFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
			}
		}

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
	}
	
	// Play Level
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

		GameEngineTexture* officeFanTexture = GameEngineTextureManager::GetInst().Find("OfficeFan.png");
		officeFanTexture->Cut(1, 3);

		GameEngineTexture* jumpScareBonnieTexture = GameEngineTextureManager::GetInst().Find("JumpScareBonnie.png");
		jumpScareBonnieTexture->Cut(1, 11);

		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareBonnie"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareChica"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFreddy"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("OfficeFan"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("LdoorClose"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("LdoorOpen"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorClose"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorOpen"));
	}
	

	// GameOver Level
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

	// Custom Setting Level
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("CustomSetting");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}


	// Intermission Level
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

	AppShaderLoad();
}