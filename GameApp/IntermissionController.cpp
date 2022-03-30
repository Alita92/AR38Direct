#include "PreCompile.h"
#include "IntermissionController.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include "IntermissionScreen.h"

DAY IntermissionController::curDay_ = DAY::DAY1;

IntermissionController::IntermissionController() // default constructer 디폴트 생성자
	: intermissionScreen_(nullptr), state_(this), deltaTime_(0.0f)
{

}

IntermissionController::~IntermissionController() // default destructer 디폴트 소멸자
{

}

void IntermissionController::StateInit()
{
	state_.CreateState("Standby", &IntermissionController::startStandby, &IntermissionController::updateStandby);
	state_.CreateState("Proceed", &IntermissionController::startProceed, &IntermissionController::updateProceed);

	state_.ChangeState("Standby");
}

void IntermissionController::SwitchDayRenderer()
{
	switch (curDay_)
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



void IntermissionController::Start()
{
	intermissionScreen_ = GetLevel()->CreateActor<IntermissionScreen>();

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
	SwitchDayRenderer();
	return StateInfo();
}

StateInfo IntermissionController::updateProceed(StateInfo _state)
{
	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (3.0f <= deltaTime_)
	{
		GetLevel()->RequestLevelChange("Play");
	}

	return StateInfo();
}