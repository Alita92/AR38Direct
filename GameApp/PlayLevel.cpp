#include "PreCompile.h"
#include "PlayLevel.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/GameEngineTransform.h>
#include <GameEngine/CameraActor.h>
#include "GameMouse.h"

#include "GameController.h"
#include "UIController.h"
#include "CurvedEffect.h"

#include <GameEngine/GameEngineGUI.h>
#include <GameEngine/GameEngineRenderWindow.h>

PlayLevel::PlayLevel()
	: gameController_(nullptr)
{
}

PlayLevel::~PlayLevel()
{
}


void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	if (nullptr == gameController_)
	{
		gameController_ = CreateActor<GameController>();
	}

	{
		curved_ = AddPostProcessCameraMergePrev<CurvedEffect>(GetMainCamera()->GetCameraRenderTarget());
		// Curved->SetTarget(GetMainCamera()->GetCameraRenderTarget());


		//GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
		//float4 Size = { 128, 72 };
		//Window->PushRenderTarget("PostEffectFade", FadeEffect->GetResult(), Size * 3);
	}

	//FadeEffect = AddPostProcessCameraMergeNext<PostFade>();
	//FadeEffect->SetTarget(GameEngineDevice::GetBackBufferTarget());

	//GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->FindGUIWindowConvert<GameEngineRenderWindow>("RenderWindow");
	//float4 Size = { 128, 72 };
	//Window->PushRenderTarget("PostEffectFade", FadeEffect->GetResult(), Size * 3);

	//FadeEffect->SetData(10, FadeOption::DARK);
	
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{
	//if (nullptr != GameEngineGUI::GetInst()->FindGUIWindow("RenderWindow"))
	{
		GameEngineRenderWindow* Window = GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineRenderWindow>("RenderWindow");
		float4 Size = { 128, 72 };
		Window->PushRenderTarget("메인 카메라 타겟", curved_->GetOriginalTarget(), Size * 3);
		Window->PushRenderTarget("포스트 프로세스 머지 타겟", GetMainCamera()->GetCameraRenderTarget(), Size * 3);
		Window->PushRenderTarget("UI 카메라 타겟", GetUICamera()->GetCameraRenderTarget(), Size * 3);
	}

}
void PlayLevel::LevelChangeEndEvent()
{
	if (nullptr != gameController_)
	{
		gameController_->ControllerReloading();
	}

	gameController_->InitEnemyAILevel();
}
void PlayLevel::LevelChangeStartEvent()
{

}
