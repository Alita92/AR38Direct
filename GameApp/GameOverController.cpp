#include "PreCompile.h"
#include "GameOverController.h"
#include "GameOverBackground.h"

GameOverController::GameOverController() // default constructer 디폴트 생성자
	: deltaTime_(0.0f), gameOverBackground_(nullptr), isWhiteNoiseOff_(false)
{

}

GameOverController::~GameOverController() // default destructer 디폴트 소멸자
{

}

void GameOverController::Start()
{
	gameOverBackground_ = GetLevel()->CreateActor<GameOverBackground>();
	gameOverBackground_->SetWhiteNoise(true);
}

void GameOverController::Update(float _Deltatime)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (WHITE_NOISE_TIME <= deltaTime_ && false == isWhiteNoiseOff_)
	{
		gameOverBackground_->SetWhiteNoise(false);
		isWhiteNoiseOff_ = true;
		deltaTime_ = 0.0f;
	}

	if (SCENE_CHANGE_TIME <= deltaTime_)
	{
		deltaTime_ = 0.0f;
		isWhiteNoiseOff_ = false;

		GetLevel()->RequestLevelChange("Title");
	}
}