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
	// ���α׷��� �������Դϴ�.
	// GameEngineCore ���� ���� ��ü�� ������ŵ�ϴ�.
	GameEngineCore::Start<UserGame>();
}