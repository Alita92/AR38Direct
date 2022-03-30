#include "PreCompile.h"
#include "GlitchScreen.h"

#include "ENUM.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>

GlitchScreen::GlitchScreen() // default constructer 디폴트 생성자
	: whiteNoiseRenderer_(nullptr), scanLineRenderer_(nullptr)
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
	whiteNoiseRenderer_->SetAlpha(0.5f);
	whiteNoiseRenderer_->Off();

	scanLineRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	scanLineRenderer_->SetImage("ScanLineStatic.png", true);
	scanLineRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::FILTER0) });
	scanLineRenderer_->CreateAnimationFolder("ScanLine", "ScanLine", 0.04f, false);
	scanLineRenderer_->CreateAnimationFolder("ScanLineFast", "ScanLine", 0.02f, false);
	//scanLineRenderer_->SetRenderGroup(static_cast<int>(UIRenderOrder::FRONT));
	scanLineRenderer_->Off();
}

void GlitchScreen::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f,0.0f,0.0f });
	ImageInit();
}

void GlitchScreen::Update(float _Deltatime)
{

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
}