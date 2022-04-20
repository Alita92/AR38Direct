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
	//ambientPlayer_.PlayOverLap("StaticShort.wav");
}

void GameOverController::Update(float _Deltatime)
{
	if (false == isWhiteNoiseOff_)
	{
		ambientPlayer_.PlayAlone("StaticShort.wav", -1);
	}

	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (WHITE_NOISE_TIME <= deltaTime_ && false == isWhiteNoiseOff_)
	{
		ambientPlayer_.Stop();
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

void GameOverController::Reloading()
{
	deltaTime_ = 0.0f;
	isWhiteNoiseOff_ = false;

}