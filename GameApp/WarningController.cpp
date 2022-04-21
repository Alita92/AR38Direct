#include "PreCompile.h"
#include "WarningController.h"

#include "FadeScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>

WarningController::WarningController() // default constructer 디폴트 생성자
	: isFadeIn_(false)
{

}

WarningController::~WarningController() // default destructer 디폴트 소멸자
{

}


void WarningController::Start()
{
	InitImage();
}

void WarningController::Update(float _Deltatime)
{
	static bool levelchange = false;

	if (false == isFadeIn_)
	{
		fadeScreen_->StartFadeIn(1.5f);

		isFadeIn_ = true;
	}

	if (true == fadeScreen_->isFullFadeIn_ && true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		fadeScreen_->StartFadeOut(1.5f);
		levelchange = true;
	}

	if (true == isFadeIn_ && true == fadeScreen_->isFullFadeOut_ && true == levelchange)
	{
		GetLevel()->RequestLevelChange("Title");
	}

}

void WarningController::InitImage()
{
	warningBackground_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	warningBackground_->SetImage("warning.png", true);
	warningBackground_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::BACKGROUND1) });

	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(1.0f);
}


void WarningController::Reloading()
{
	warningBackground_->SetImage("warning.png", true);
	warningBackground_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::BACKGROUND1) });

	isFadeIn_ = false;
	fadeScreen_->Reset();
	fadeScreen_->SetAlpha(1.0f);
}