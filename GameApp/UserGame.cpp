#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>
#include <GameEngine\GameEngineLevelControlWindow.h>

#include "WarningLevel.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "GameOverLevel.h"
#include "IntermissionLevel.h"
#include "CustomSettingLevel.h"
#include "TrialOverLevel.h"

#include <GameEngine\GameEngineRenderWindow.h>

std::atomic<int> UserGame::LoadingFolder = 0;

UserGame::UserGame() 
{
}

UserGame::~UserGame() 
{
}

UserGame::UserGame(UserGame&& _other) noexcept  
{
}

void UserGame::Initialize()
{
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");

	LevelCreate<WarningLevel>("Warning");
	LevelCreate<TitleLevel>("Title");
	LevelCreate<IntermissionLevel>("Intermission");
	LevelCreate<PlayLevel>("Play");
	LevelCreate<GameOverLevel>("GameOver");
	LevelCreate<CustomSettingLevel>("CustomSetting");
	LevelCreate<TrialOverLevel>("TrialOver");

	LevelChange("Warning");
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
		GameEngineInput::GetInst().CreateKey("ESC", VK_ESCAPE);

		// **** FOR DEMONSTRATION AND DEBUGGING ****
		GameEngineInput::GetInst().CreateKey("DEBUG_RECT", 'L');
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPHOUR", 'I');
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPELEC", 'O');

		GameEngineInput::GetInst().CreateKey("FreeCamera_Toggle", 'P');

		GameEngineInput::GetInst().CreateKey("Freddy", 'V');
		GameEngineInput::GetInst().CreateKey("Bonnie", 'B');
		GameEngineInput::GetInst().CreateKey("Chica", 'N');
		GameEngineInput::GetInst().CreateKey("Foxy", 'M');
	}
}
