#pragma once
#include <GameEngine/GameEngineActor.h>

class GameOverBackground;
class GameOverController : public GameEngineActor
{
public:
	GameOverController(); // default constructer 디폴트 생성자
	~GameOverController(); // default destructer 디폴트 소멸자
	GameOverController(const GameOverController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameOverController(GameOverController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameOverController& operator=(const GameOverController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameOverController& operator=(const GameOverController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

protected:
	GameOverBackground* gameOverBackground_;

private:
	const float WHITE_NOISE_TIME = 5.0f;
	const float SCENE_CHANGE_TIME = 5.0f;

	float deltaTime_;
	bool isWhiteNoiseOff_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

