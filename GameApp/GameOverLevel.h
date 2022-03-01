#pragma once
#include <GameEngine/GameEngineLevel.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameOverLevel : public GameEngineLevel
{
public:
	GameOverLevel();
	~GameOverLevel();
	GameOverLevel(const GameOverLevel& _other) = delete;
	GameOverLevel(GameOverLevel&& _other) noexcept;
	GameOverLevel& operator=(const GameOverLevel& _other) = delete;
	GameOverLevel& operator=(const GameOverLevel&& _other) noexcept = delete;
protected:		

private:		
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

private:
	void ResourceInit();
};

