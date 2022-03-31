#include "PreCompile.h"
#include "GlitchScreen.h"

#include "ENUM.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>

GlitchScreen::GlitchScreen() // default constructer 디폴트 생성자
	: whiteNoiseRenderer_(nullptr), scanLineRenderer_(nullptr), subScanLineRenderer_(nullptr), generalInterTime_(0.0f), changeInterTime_(0.0f), timeDice_(0), changeDice_(0), isFirstSessionOut_(false), isStatic_(false)
{

}

GlitchScreen::~GlitchScreen() // default destructer 디폴트 소멸자
{

}

void GlitchScreen::ImageInit()
{
	whiteNoiseRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	whiteNoiseRenderer_->SetImage("WhiteNoiseStatic.png", true);
	whiteNoiseRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::FILTER1)});
	//whiteNoiseRenderer_->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));
	whiteNoiseRenderer_->CreateAnimationFolder("WhiteNoise", "WhiteNoise", 0.02f, true);
	whiteNoiseRenderer_->SetChangeAnimation("WhiteNoise");
	whiteNoiseRenderer_->Off();

	scanLineRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	scanLineRenderer_->SetImage("ScanLineStatic.png", true);
	scanLineRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::FILTER0) });
	scanLineRenderer_->CreateAnimationFolder("ScanLine", "ScanLine", 0.04f, false);
	scanLineRenderer_->CreateAnimationFolder("ScanLineFast", "ScanLine", 0.02f, false);
	//scanLineRenderer_->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));
	scanLineRenderer_->Off();

	subScanLineRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	subScanLineRenderer_->SetImage("SubScanLine.png", true);
	subScanLineRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 384.0f,static_cast<int>(RenderOrder::FILTER1) });
	subScanLineRenderer_->Off();

}

void GlitchScreen::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	ImageInit();
}

void GlitchScreen::Update(float _Deltatime)
{
	if (true == subScanLineRenderer_->IsUpdate() && false == isStatic_)
	{
		if (-384.0f >= subScanLineRenderer_->GetTransform()->GetLocalPosition().y)
		{
			subScanLineRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 384.0f, static_cast<int>(RenderOrder::FILTER1) });
		}

		subScanLineRenderer_->GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * SCANLINE_DOWNSPEED);
	}

}

void GlitchScreen::SetWhiteNoiseAlpha(float _alpha)
{
	whiteNoiseRenderer_->SetAlpha(_alpha);
}

void GlitchScreen::PlayWhiteNoise(bool _on)
{
	if (true == _on)
	{
		whiteNoiseRenderer_->On();
		return;
	}
	else
	{
		whiteNoiseRenderer_->Off();
	}
}

void GlitchScreen::PlayAwakeScanLine()
{
	scanLineRenderer_->On();
	scanLineRenderer_->SetChangeAnimation("ScanLine", true);
}


void GlitchScreen::PlayAwakeScanLineFast()
{
	scanLineRenderer_->On();
	scanLineRenderer_->SetChangeAnimation("ScanLineFast", true);
}

void GlitchScreen::SetStatic()
{
	whiteNoiseRenderer_->SetImage("WhiteNoiseStatic.png", true);
	isStatic_ = true;
}

void GlitchScreen::SetSubRenderer(bool _on)
{
	if (true == _on)
	{
		subScanLineRenderer_->SetAlpha(0.2f);
		subScanLineRenderer_->On();
	}
	else
	{
		subScanLineRenderer_->SetAlpha(1.0f);
		subScanLineRenderer_->Off();
	}
}

void GlitchScreen::ScanLineRandomChange()
{
	if (true == isStatic_)
	{
		return;
	}

	if (false == scanLineRenderer_->IsUpdate())
	{
		scanLineRenderer_->On();
		scanLineRenderer_->SetAlpha(0.2f);
	}

	generalInterTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (false == isFirstSessionOut_ && 8.0f <= generalInterTime_)
	{
		timeDice_ = randomGenerator_.RandomInt(0, 4);
		changeDice_ = randomGenerator_.RandomInt(0, 6);
		generalInterTime_ = 0.0f;
		isFirstSessionOut_ = true;
		return;
	}

	switch (timeDice_)
	{
	case 0:
	case 1:
		if (0.05f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 2:
		if (0.1f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 3:
		if (1.5f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 4:
		if (3.0f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	default:
		break;
	}

	return;
}

void GlitchScreen::RandomImageChange()
{
	changeInterTime_ += GameEngineTime::GetInst().GetDeltaTime();

	switch (changeDice_)
	{
	case 0:
		scanLineRenderer_->SetImage("TitleScanLine001.png", true);
		break;
	case 1:
		scanLineRenderer_->SetImage("TitleScanLine002.png", true);
		break;
	case 2:
		scanLineRenderer_->SetImage("TitleScanLine003.png", true);
		break;
	case 3:
		scanLineRenderer_->SetImage("TitleScanLine004.png", true);
		break;
	case 4:
		scanLineRenderer_->SetImage("TitleScanLine005.png", true);
		break;
	case 5:
		scanLineRenderer_->SetImage("TitleScanLine006.png", true);
		break;
	case 6:
		scanLineRenderer_->SetImage("TitleScanLine007.png", true);
		break;
	default:
		break;
	}

	if (0.05f <= changeInterTime_)
	{
		// 마무리 초기화
		timeDice_ = randomGenerator_.RandomInt(0, 4);
		changeDice_ = randomGenerator_.RandomInt(0, 6);
		generalInterTime_ = 0.0f;
		changeInterTime_ = 0.0f;
		scanLineRenderer_->SetImage("ScanLineStatic.png", true);
		return;
	}
}