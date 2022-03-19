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
		//		// ������ ��� ���ҽ��� for �� Ÿ�� �ٴϸ� ��� �ؽ�ó�� Load �� �ش�.
		//		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		//	}
	}

	AppShaderLoad();
}