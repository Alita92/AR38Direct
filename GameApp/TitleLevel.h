#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

// ���� :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete; 

public:
	void SetNextLevel(Level _nextLevel);

protected:
	Level nextLevel_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

private:
	void ResourceInit();

private:
	void CheckLevelChangeRequest();
	bool isUIButtonDown_;
};

