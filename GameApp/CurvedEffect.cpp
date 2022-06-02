#include "PreCompile.h"
#include "CurvedEffect.h"

CurvedEffect::CurvedEffect(GameEngineRenderTarget* RenderTarget)
{
	Target_ = RenderTarget;
}

CurvedEffect::~CurvedEffect() 
{
}


void CurvedEffect::Effect(float _DeltaTime)
{
	prevTarget_->Clear();
	prevTarget_->Copy(Target_);

	Result_->Clear();
	Result_->Setting();
	Res_.Setting();
	Effect_->Rendering();
	Effect_->Reset();
	Res_.ReSet();

	Target_->Clear(false);
	Target_->Copy(Result_);
}

void CurvedEffect::Initialize()
{
	CreateResultTarget();
	CreatePrevTarget();
	SetEffect("Curved");
	Res_.SettingTexture("Tex", Target_->GetTexture(0));
	Res_.SettingTexture("TexUV", "CurvedUV.png");
}
