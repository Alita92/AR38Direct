#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include "ENUM.h"

class GameEngineImageRenderer;
class FadeScreen;
class TrialOverController : public GameEngineActor
{
private:
	friend class TrialOverLevel;

public:
	TrialOverController(); // default constructer 디폴트 생성자
	~TrialOverController(); // default destructer 디폴트 소멸자
	TrialOverController(const TrialOverController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TrialOverController(TrialOverController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	TrialOverController& operator=(const TrialOverController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TrialOverController& operator=(const TrialOverController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	FadeScreen* fadeScreen_;
	GameEngineImageRenderer* trialOverBackground_;
	GameEngineSoundPlayer ambientPlayer_;

private:
	void InitImage();
	void Reloading();

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	bool isFadeIn_;
	bool isLevelChanged_;
};

