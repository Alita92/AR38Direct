#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
class GameEngineImageRenderer;
class WarningLevel;
class FadeScreen;
class WarningController : public GameEngineActor
{
private:
	friend WarningLevel;
public:
	WarningController(); 
	~WarningController(); 
	WarningController(const WarningController& _other) = delete;
	WarningController(WarningController&& _other) noexcept;
	WarningController& operator=(const WarningController& _other) = delete; 
	WarningController& operator=(const WarningController&& _other) noexcept = delete;

protected:
	FadeScreen* fadeScreen_;
	GameEngineImageRenderer* warningBackground_;

private:
	void InitImage();
	void Reloading();

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	bool isFadeIn_;
};

