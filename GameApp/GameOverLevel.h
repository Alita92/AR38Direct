#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameOverLevel : public GameEngineLevel
{
private:
	friend class GameOverController;

public:
	GameOverLevel();
	~GameOverLevel();
	GameOverLevel(const GameOverLevel& _other) = delete;
	GameOverLevel(GameOverLevel&& _other) noexcept;
	GameOverLevel& operator=(const GameOverLevel& _other) = delete;
	GameOverLevel& operator=(const GameOverLevel&& _other) noexcept = delete;

protected:		
	GameOverController* controller_;


private:		
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

