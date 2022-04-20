#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>
#include <GameEngine\GameEngineLevelControlWindow.h>

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "GameOverLevel.h"
#include "IntermissionLevel.h"
#include "CustomSettingLevel.h"
#include "TrialOverLevel.h"

#include <GameEngine\GameEngineRenderWindow.h>

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
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");

	LevelCreate<TitleLevel>("Title");
	LevelCreate<IntermissionLevel>("Intermission");
	LevelCreate<PlayLevel>("Play");
	LevelCreate<GameOverLevel>("GameOver");
	LevelCreate<CustomSettingLevel>("CustomSetting");
	LevelCreate<TrialOverLevel>("TrialOver");

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
		GameEngineInput::GetInst().CreateKey("RotateRight", 'Z');
		GameEngineInput::GetInst().CreateKey("RotateLeft", 'C');
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
//		// 랜더링 파이프라인이 하나가 돌고
//		// 이안에 세팅정보가 존재하겠죠?
//		GameEngineDevice::RenderStart();
//
//		// 매프레임마다 세팅해줘야 하는게 되죠?
//		// 
//		Pipe->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}
//
//
