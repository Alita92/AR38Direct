#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRenderer.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"
#include "CameraActor.h"
#include "CameraComponent.h"


CameraActor* GameEngineLevel::GetMainCameraActor()
{
	// 레벨 수준에서 제공되는 카메라 액터
	return MainCameraActor_;
}

CameraComponent* GameEngineLevel::GetMainCamera()
{
	return MainCameraActor_->GetCamera();
}

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}

		}
	}
}

void GameEngineLevel::Init()
{
	MainCameraActor_ = CreateActor<CameraActor>();
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	// 리스트에 소속된 액터를 순회하며 업데이트를 실행시킨다.

	// Transform 업데이트 순회
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->TransformUpdate();
		}
	}

	// 일반 업데이트 순회
	for (std::pair<int, std::list<GameEngineActor*>> Pair : ActorList_)
	{
		std::list<GameEngineActor*>& Actors = Pair.second;

		for (GameEngineActor* Actor : Actors)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->Update(_DeltaTime);
		}
	}
}

void GameEngineLevel::Render()
{
	// 디바이스의 RenderStart() 를 통해 백버퍼 렌더타겟을 클리어 후 셋업해준다.
	GameEngineDevice::RenderStart();


	// 
	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}
		}
	}


	// 렌더러 리스트 자료들을 돌며 Render() 를 실행한다.
	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;
		// 메인 카메라의 뷰행렬과 투영 행렬을 가져온다.
		float4x4 View = MainCameraActor_->GetViewMatrix();
		float4x4 Porjection = MainCameraActor_->GetPorjectionMatrix();

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				// 활성화가 되어 있지 않은 렌더러는 패스
				continue;
			}

			// 렌더러에 가져 온 뷰행렬과 투영 행렬값을 넣어 준다.
			Renderer->GetTransform()->GetTransformData().Projection_ = Porjection;
			Renderer->GetTransform()->GetTransformData().View_ = View;

			// 완성된 렌더러를 렌더링해준다
			Renderer->Render();
		}
	}

	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::PushRenderer(int _Order, GameEngineRenderer* _Renderer)
{
	RendererList_[_Order].push_back(_Renderer);
}


void GameEngineLevel::LevelChangeStartEvent()
{

}

void GameEngineLevel::LevelChangeEndEvent()
{

}