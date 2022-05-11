#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

class GameOverBackground;
class GameOverController : public GameEngineActor
{
private:
	friend class GameOverLevel;

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
	GameEngineSoundPlayer ambientPlayer_;

private:
	const float WHITE_NOISE_TIME = 5.0f;
	const float SCENE_CHANGE_TIME = 5.0f;

	float deltaTime_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void Reloading();


private:
	GameEngineFSM<GameOverController> state_;
	void InitState();

#pragma region States
	StateInfo startWhiteNoise(StateInfo _state);
	StateInfo updateWhiteNoise(StateInfo _state);

	StateInfo startGameOver(StateInfo _state);
	StateInfo updateGameOver(StateInfo _state);
#pragma endregion States
};

