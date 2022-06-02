#include "PreCompile.h"
#include "TrialOverController.h"

#include "FadeScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>


TrialOverController::TrialOverController() // default constructer ����Ʈ ������
	: trialOverBackground_(nullptr), isFadeIn_(false), isLevelChanged_(false)
{

}

TrialOverController::~TrialOverController() // default destructer ����Ʈ �Ҹ���
{

}

void TrialOverController::Start()
{
	InitImage();
}

void TrialOverController::Update(float _Deltatime)
{

	if (false == isFadeIn_)
	{
		ambientPlayer_.PlayAlone("MusicBox.wav");

		fadeScreen_->StartBright(1.5f);

		isFadeIn_ = true;
	}

	if (true == fadeScreen_->isFullBright_ && true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		fadeScreen_->StartDark(1.5f);
		isLevelChanged_ = true;
	}

	if (true == isFadeIn_ && true == fadeScreen_->isFullDark_ && true == isLevelChanged_)
	{
		ambientPlayer_.Stop();
		GetLevel()->RequestLevelChange("Warning");
	}


}

void TrialOverController::InitImage()
{
	trialOverBackground_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	trialOverBackground_->SetImage("EndingRed.png", true);
	trialOverBackground_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::BACKGROUND1) });

	fadeScreen_ = GetLevel()->CreateActor<FadeScreen>();
	fadeScreen_->SetAlpha(1.0f);
}


void TrialOverController::Reloading()
{
	trialOverBackground_->SetImage("EndingRed.png", true);
	trialOverBackground_->GetTransform()->SetLocalPosition({ 0.0f,0.0f,static_cast<int>(RenderOrder::BACKGROUND1) });

	isFadeIn_ = false;
	isLevelChanged_ = false;
	fadeScreen_->Reset();
	fadeScreen_->SetAlpha(1.0f);
}