#include "PreCompile.h"
#include "IntermissionController.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include "IntermissionScreen.h"
#include "FadeScreen.h"
#include "GlitchScreen.h"

#include "GameStaticData.h"

IntermissionController::IntermissionController() // default constructer ����Ʈ ������
	: intermissionScreen_(nullptr), state_(this), deltaTime_(0.0f), fadeScreen_(nullptr), glitchScreen_(nullptr)
{

}

IntermissionController::~IntermissionController() // default destructer ����Ʈ �Ҹ���
{

}

void IntermissionController::StateInit()
{
	state_.CreateState("Standby", &IntermissionController::startStandby, &IntermissionController::updateStandby);
	state_.CreateState("Proceed", &IntermissionController::startProceed, &IntermissionController::updateProceed);
	state_.CreateState("FadeOut", &IntermissionController::startFadeOut, &IntermissionController::updateFadeOut);

	state_.ChangeState("Standby");
}

void IntermissionController::SwitchDayRenderer()
{
	switch (GameStaticData::curDay_)
	{
	case DAY::DAY1:
		intermissionScreen_->typoRenderer_->SetImage("Day1.png", true);
		break;
	case DAY::DAY2:
		intermissionScreen_->typoRenderer_->SetImage("Day2.png", true);
		break;
	case DAY::DAY3:
		intermissionScreen_->typoRenderer_->SetImage("Day3.png", true);
		break;
	case DAY::DAY4:
		intermissionScreen_->typoRenderer_->SetImage("Day4.png", true);
		break;
	case DAY::DAY5:
		intermissionScreen_->typoRenderer_->SetImage("Day5.png", true);
		break;
	case DAY::DAY6:
		intermissionScreen_->typoRenderer_->SetImage("Day6.png", true);
		break;
	case DAY::CUSTOM:
		intermissionScreen_->typoRenderer_->SetImage("Day7.png", true);
		break;
	case DAY::MAX:
		break;
	default:
		break;
	}
}

void IntermissionController::ControllerReloading()
{
	state_.ChangeState("Standby");
	fadeScreen_->SetAlpha(0.0f);
	fadeScreen_->StartFadeIn(0.0f);
}

void IntermissionController::Start()
{

	intermissionScreen_ = GetLevel()->CreateActor<IntermissionScreen>();
	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(0.0f);
	glitchScreen_ = GetLevel()->CreateActor<GlitchScreen>();
	StateInit();
}

void IntermissionController::Update(float _Deltatime)
{
	state_.Update();
}

StateInfo IntermissionController::startStandby(StateInfo _state)
{
	return StateInfo();
}

StateInfo IntermissionController::updateStandby(StateInfo _state)
{

	return "Proceed";
}

StateInfo IntermissionController::startProceed(StateInfo _state)
{
	glitchScreen_->PlayAwakeScanLine();
	SwitchDayRenderer();
	return StateInfo();
}

StateInfo IntermissionController::updateProceed(StateInfo _state)
{

	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (1.5f <= deltaTime_)
	{
		fadeScreen_->StartFadeOut(3.2f);
	}

	if (true == fadeScreen_->isFullFadeOut_)
	{
		return "FadeOut";
	}

	return StateInfo();
}

StateInfo IntermissionController::startFadeOut(StateInfo _state)
{
	return StateInfo();
}

StateInfo IntermissionController::updateFadeOut(StateInfo _state)
{

	GetLevel()->RequestLevelChange("Play");
	return StateInfo();
}