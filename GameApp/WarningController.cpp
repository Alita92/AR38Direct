#include "PreCompile.h"
#include "WarningController.h"

#include "FadeScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>

WarningController::WarningController() // default constructer 디폴트 생성자
	: isFadeIn_(false), isLevelChange_(false), fadeScreen_(nullptr), warningBackground_(nullptr),deltaTime_(0.0f)
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

	deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (false == isFadeIn_)
	{
		fadeScreen_->StartFadeIn(1.5f);

		isFadeIn_ = true;
	}

	if (true == fadeScreen_->isFullFadeIn_ && true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		deltaTime_ = 0.0f;
		fadeScreen_->StartFadeOut(1.5f);
		isLevelChange_ = true;
	}
	else if (true == fadeScreen_->isFullFadeIn_ && 3.0f <= deltaTime_ && false == isLevelChange_)
	{
		fadeScreen_->StartFadeOut(1.5f);
		isLevelChange_ = true;
	}

	if (true == isFadeIn_ && true == fadeScreen_->isFullFadeOut_ && true == isLevelChange_)
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
	deltaTime_ = 0.0f;
	isLevelChange_ = false;
	fadeScreen_->Reset();
	fadeScreen_->SetAlpha(1.0f);
}