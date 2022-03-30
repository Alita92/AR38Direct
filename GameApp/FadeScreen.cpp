#include "PreCompile.h"
#include "FadeScreen.h"

#include "ENUM.h"
#include <GameEngine/GameEngineImageRenderer.h>

FadeScreen::FadeScreen() // default constructer ����Ʈ ������
	: fadeScreenRenderer_(nullptr), loadingClockRenderer_(nullptr), deltaTime_(0.0f), isFadeIn_(false), isFadeOut_(false), divider_(0.0f), isFullFadeIn_(false), isFullFadeOut_(false)
{

}

FadeScreen::~FadeScreen() // default destructer ����Ʈ �Ҹ���
{

}


void FadeScreen::ImageInit()
{
	fadeScreenRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	fadeScreenRenderer_->SetImage("ClearScreen.png", true);
	fadeScreenRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<float>(RenderOrder::FADE2) });
	
	loadingClockRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	loadingClockRenderer_->SetImage("LoadingClock.png" , true);
	loadingClockRenderer_->GetTransform()->SetLocalPosition({ 500.0f, -330.0f,static_cast<float>(RenderOrder::FADE1) });
	loadingClockRenderer_->Off();
}

void FadeScreen::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	ImageInit();
}

void FadeScreen::Update(float _Deltatime)
{
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
		// ��ŸŸ���� ���������� �پ��� �� 0~1 ���̷� ǥ���ؾ� �Ѵ�...

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

void FadeScreen::SetStartAlpha(float _alpha)
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

void FadeScreen::ReleaseScreen(float _time)
{
	_time -= GameEngineTime::GetInst().GetDeltaTime();

	if (0.0f >= _time)
	{
		fadeScreenRenderer_->Off();
		if (true == loadingClockRenderer_->IsUpdate())
		{
			loadingClockRenderer_->Off();
		}
	}
}