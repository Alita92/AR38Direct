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
		//	GameEngineDirectory TextureDir;
		//	TextureDir.MoveParent("AR38Direct");
		//	TextureDir.MoveChild("Resources");
		//	TextureDir.MoveChild("Image");
		//
		//	std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
		//	
		//	for (size_t i = 0; i < AllFile.size(); i++)
		//	{
		//		// 가져온 모든 리소스를 for 로 타고 다니며 모두 텍스처로 Load 해 준다.
		//		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		//	}
	}

	AppShaderLoad();
}