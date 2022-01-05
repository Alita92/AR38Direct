#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
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


		GameEngineSound::GetInst().LoadSound("Bgm.mp3", SoundDir.PathToPlusFileName("Bgm.mp3"));
	}



	GameEngineSound::GetInst().PlaySoundOneShot("Bgm.mp3");

}

void UserGame::Release()
{
	GameEngineSound::Destroy();
}

void UserGame::GameLoop()
{
	switch (_getch())
	{
	case 'q':
	case 'Q':
		EngineDestroy();
		return;
	default:
		break;
	};
}