#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class GameController;
class CurvedEffect;
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	GameController* gameController_;
	CurvedEffect* curved_;
	
private:
	void CreateActorLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

