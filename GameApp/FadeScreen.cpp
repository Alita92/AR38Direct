#include "PreCompile.h"
#include "FadeScreen.h"

#include "ENUM.h"
#include <GameEngine/GameEngineUIRenderer.h>

FadeScreen::FadeScreen() // default constructer 디폴트 생성자
	: fadeScreenRenderer_(nullptr), loadingClockRenderer_(nullptr), deltaTime_(0.0f), isFadeIn_(false)
	, isFadeOut_(false), divider_(0.0f), isFullFadeIn_(false), isFullFadeOut_(false), isReleaseOn_(false), releaseTime_(0.0f)
{

}

FadeScreen::~FadeScreen() // default destructer 디폴트 소멸자
{

}


void FadeScreen::ImageInit()
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
	ImageInit();
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
		isFullFadeOut_ = true;
	}
	else
	{
		isFullFadeOut_ = false;
	}

	if (0.01f >= fadeScreenRenderer_->GetAlpha())
	{
		isFullFadeIn_ = true;
	}
	else
	{
		isFullFadeIn_ = false;
	}


	if (true == isFadeIn_ && false == isFadeOut_)
	{
		deltaTime_ -= GameEngineTime::GetInst().GetDeltaTime();
		// 델타타임이 일정량으로 줄어드는 걸 0~1 사이로 표현해야 한다...

		if (0.0f <= deltaTime_)
		{
			fadeScreenRenderer_->SetAlpha(deltaTime_ / divider_);
		}
	}
	else if (true == isFadeOut_ && false == isFadeIn_)
	{
		deltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

		if (divider_ >= deltaTime_)
		{
			fadeScreenRenderer_->SetAlpha(deltaTime_ / divider_);
		}
	}
}

void FadeScreen::SetAlpha(float _alpha)
{
	fadeScreenRenderer_->SetAlpha(_alpha);
}

void FadeScreen::StartFadeIn(float _time)
{
	deltaTime_ = _time;
	divider_ = _time;
	isFadeOut_ = false;
	isFadeIn_ = true;
}

void FadeScreen::StartFadeOut(float _time)
{
	divider_ = _time;
	isFadeIn_ = false;
	isFadeOut_ = true;
}

void FadeScreen::SetLoadingRenderer()
{
	loadingClockRenderer_->On();
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