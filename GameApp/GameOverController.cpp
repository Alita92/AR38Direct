#include "PreCompile.h"
#include "GameOverController.h"
#include "GameOverBackground.h"

GameOverController::GameOverController() // default constructer 디폴트 생성자
	: deltaTime_(0.0f), gameOverBackground_(nullptr), state_(this)
{

}

GameOverController::~GameOverController() // default destructer 디폴트 소멸자
{

}

void GameOverController::InitState()
{
	state_.CreateState("WhiteNoise", &GameOverController::startWhiteNoise, &GameOverController::updateWhiteNoise);
	state_.CreateState("GameOver", &GameOverController::startGameOver, &GameOverController::updateGameOver);
	state_.ChangeState("WhiteNoise");
}

void GameOverController::Start()
{
	gameOverBackground_ = GetLevel()->CreateActor<GameOverBackground>();
	gameOverBackground_->SetWhiteNoise(true);
	InitState();
	//ambientPlayer_.PlayOverLap("StaticShort.wav");
}

void GameOverController::Update(float _Deltatime)
{
	state_.Update();
}

void GameOverController::Reloading()
{
	state_.ChangeState("WhiteNoise");
	gameOverBackground_->SetWhiteNoise(true);
	deltaTime_ = 0.0f;
}

StateInfo GameOverController::startWhiteNoise(StateInfo _state)
{


	return StateInfo();
}

StateInfo GameOverController::updateWhiteNoise(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();
	ambientPlayer_.PlayAlone("StaticShort.wav");
	if (WHITE_NOISE_TIME <= deltaTime_)
	{
		ambientPlayer_.Stop();
		gameOverBackground_->SetWhiteNoise(false);
		deltaTime_ = 0.0f;
		return "GameOver";
	}

	return StateInfo();
}

StateInfo GameOverController::startGameOver(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameOverController::updateGameOver(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (SCENE_CHANGE_TIME <= deltaTime_)
	{
		deltaTime_ = 0.0f;

		GetLevel()->RequestLevelChange("Title");
	}

	return StateInfo();
}