#include "PreCompile.h"
#include "IntermissionScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>

static IntermissionScreen::curDay_ = nullptr;

IntermissionScreen::IntermissionScreen() // default constructer 디폴트 생성자
	: mainRenderer_(nullptr), typoRenderer_(nullptr)
{

}

IntermissionScreen::~IntermissionScreen() // default destructer 디폴트 소멸자
{

}

void IntermissionScreen::PromoteIntermissionTo(DAY _day)
{
	curDay_ = _day;

	switch (curDay_)
	{
	case DAY::DAY1:
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("Newspaper.png");

		typoRenderer_ = nullptr;
	}
		break;
	case DAY::DAY2:
		break;
	case DAY::DAY3:
		break;
	case DAY::DAY4:
		break;
	case DAY::DAY5:
		break;
	case DAY::CUSTOM:
		// 보류... 6th day 로 해야하나?
		break;
	case DAY::MAX:
		break;
	default:
		break;
	}
}

void IntermissionScreen::Start()
{
	curDay_ = DAY::DAY1;
	PromoteIntermissionTo(curDay_);


}

void IntermissionScreen::Update(float _DeltaTime)
{

}