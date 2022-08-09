#include "PreCompile.h"

#include <conio.h>
#include <GameEngine/GameEngineCore.h>
#include "UserGame.h"



int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	// 프로그램의 진입점입니다.
	// GameEngineCore 에서 게임 자체를 구동시킵니다.
	GameEngineCore::Start<UserGame>();
}