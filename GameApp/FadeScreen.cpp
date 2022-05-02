#include "PreCompile.h"
#include "FadeScreen.h"

#include "ENUM.h"
#include <GameEngine/GameEngineUIRenderer.h>

FadeScreen::FadeScreen() // default constructer 디폴트 생성자
	: fadeScreenRenderer_(nullptr), loadingClockRenderer_(nullptr), deltaTime_(0.0f), isBright_(true)
	, isDark_(false), divider_(0.0f), isFullDark_(false), isFullBright_(true), isReleaseOn_(false), releaseTime_(0.0f)
{
}

FadeScreen::~FadeScreen() // default destructer 디폴트 소멸자
{

}

void FadeScreen::Reset()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	loadingClockRenderer_->Off();
	deltaTime_ = 0.0f;
	isDark_ = false;
	isBright_ = true;
	divider_ = 0.0f;
	isFullDark_ = false;
	isFullBright_ = true;
	isReleaseOn_ = false;
	releaseTime_ = 0.0f;
}

void FadeScreen::InitImage()
{
	fadeScreenRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	fadeScreenRenderer_->SetImage("ClearScreen.png", true);
	fadeScreenRenderer_->SetRenderGroup(static_cast<int>(UIRenderOrder::FADE2));

	loadingClockRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	loadingClockRenderer_->SetImage("LoadingClock.png", true);
	loadingClockRenderer_->GetTransform()->SetLocalPosition({ 600.0f, -330.0f, 0.0f });
	loadingClockRenderer_->SetRenderGroup(static_cast<int>(UIRenderOrder::FADE1));
	loadingClockRenderer_->Off();
}


void FadeScreen::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	InitImage();
}

void FadeScreen::Update(float _Deltatime)
{
	if (true == isReleaseOn_)
	{
		releaseTime_ -= GameEngineTime::GetInst().GetDeltaTime();

		if (0.0f >= releaseTime_)
		{
			fadeScreenRenderer_->Off();
			if (true == loadingClockRenderer_->IsUpdate())
			{
				loadingClockRenderer_->Off();
			}
		}
	}

	if (0.99f <= fadeScreenRenderer_->GetAlpha())
	{
		isFullDark_ = true;
	}
	else
	{
		isFullDark_ = false;
	}

	if (0.01f >= fadeScreenRenderer_->GetAlpha())
	{
		isFullBright_ = true;
	}
	else
	{
		isFullBright_ = false;
	}


	if (true == isBright_ && false == isDark_)
	{
		deltaTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		// 델타타임이 일정량으로 줄어드는 걸 0~1 사이로 표현해야 한다...

		if (0.0f <= deltaTime_)
		{
			fadeScreenRenderer_->SetAlpha(deltaTime_ / divider_);
		}
	}
	else if (true == isDark_ && false == isBright_)
	{
		deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

		if (divider_ >= deltaTime_)
		{
			fadeScreenRenderer_->SetAlpha(deltaTime_ / divider_);
		}
	}
	else if (true == isDark_ && true == isBright_)
	{
		return;
	}
}

void FadeScreen::SetAlpha(float _alpha)
{
	fadeScreenRenderer_->SetAlpha(_alpha);
}

void FadeScreen::StartDark(float _time)
{
	deltaTime_ = 0.0f;
	divider_ = _time;
	isBright_ = false;
	isDark_ = true;
}

void FadeScreen::StartBright(float _time)
{
	deltaTime_ = _time;
	divider_ = _time;
	isDark_ = false;
	isBright_ = true;
}

void FadeScreen::SetLoadingRenderer()
{
	loadingClockRenderer_->On();
}

void FadeScreen::RemoveLoadingRenderer()
{
	loadingClockRenderer_->Off();
}

void FadeScreen::OffScreen(float _time)
{
	releaseTime_ = _time;
	isReleaseOn_ = true;
}

void FadeScreen::OnScreen()
{
	releaseTime_ = 0.0f;
	isReleaseOn_ = false;
	fadeScreenRenderer_->On();
}