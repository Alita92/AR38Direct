#pragma once
#include <GameEngine/GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 

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

protected:
	GameEngineImageRenderer* gameOverBackgroundRenderer_;
	GameEngineImageRenderer* gameOverTextRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

