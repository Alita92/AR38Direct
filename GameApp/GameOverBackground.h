#pragma once
#include <GameEngine/GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 

class GlitchScreen;
class GameEngineImageRenderer;
class GameOverBackground : public GameEngineActor
{
public:
	GameOverBackground();
	~GameOverBackground();
	GameOverBackground(const GameOverBackground& _other) = delete;
	GameOverBackground(GameOverBackground&& _other) noexcept; 
	GameOverBackground& operator=(const GameOverBackground& _other) = delete;
	GameOverBackground& operator=(const GameOverBackground&& _other) noexcept = delete;

public:
	void SetWhiteNoise(bool _on);

protected:
	GlitchScreen* gameOverGlitchScreen_;
	GameEngineImageRenderer* gameOverBackgroundRenderer_;
	GameEngineImageRenderer* gameOverTextRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitImage();
};

