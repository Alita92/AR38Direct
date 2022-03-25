#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "GameOverLevel.h"
#include "CustomSettingLevel.h"

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
	//TransData.View.ViewToLH( { 0.0f, 0.0f, -10.0f }, {0.0f, 0.0f , 1.0f}, {0.0f, 1.0f , 0.0f});

	//TransData.Proj.OrthographicLH( 1280.f, 720.f, 0.1f, 1000.0f );


	//TransData.Scale.Scaling2D(200.0f);
	//TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	//TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	//TransData.CalWorld();

	//GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	//Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);

	GameEngineInput::GetInst().HideCursor();
	

	LevelCreate<TitleLevel>("Title");
	LevelCreate<PlayLevel>("Play");

	LevelCreate<GameOverLevel>("GameOver");
	LevelCreate<CustomSettingLevel>("CustomSetting");

	LevelChange("Title");
	KeyInit();
	return;
}

void UserGame::Release()
{

}


void UserGame::KeyInit()
{
	if (false == GameEngineInput::GetInst().IsKey("MOUSE_1"))
	{
		GameEngineInput::GetInst().CreateKey("MOUSE_1", VK_LBUTTON);
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIP", 'P');
		GameEngineInput::GetInst().CreateKey("ESC", VK_ESCAPE);

		GameEngineInput::GetInst().CreateKey("LDoor_Toggle", 'Q');
		GameEngineInput::GetInst().CreateKey("RDoor_Toggle", 'E');
		GameEngineInput::GetInst().CreateKey("LLight_Toggle", 'A');
		GameEngineInput::GetInst().CreateKey("RLight_Toggle", 'D');

		GameEngineInput::GetInst().CreateKey("CCTV_Toggle", 'X');
		GameEngineInput::GetInst().CreateKey("CCTV_NEXT", 'Z');
		GameEngineInput::GetInst().CreateKey("CCTV_PREV", 'C');

	}
}

//
//void UserGame::GameLoop()
//{
//	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
//	{
//		Pos.x += 0.001f;
//		TransData.Position.Translation(Pos);
//		TransData.CalWorld();
//
//
//		// ������ ������������ �ϳ��� ����
//		// �̾ȿ� ���������� �����ϰ���?
//		GameEngineDevice::RenderStart();
//
//		// �������Ӹ��� ��������� �ϴ°� ����?
//		// 
//		Pipe->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}
//
//
