#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}



void UserGame::Initialize()
{

	GameEngineSound::GetInst().Initialize();
	return;
}

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
			GameEngineSound::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}


}

void UserGame::Release()
{
	GameEngineSound::Destroy();
}

void UserGame::GameLoop()
{


}