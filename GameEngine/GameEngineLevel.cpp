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
	// ���� ���ؿ��� �����Ǵ� ī�޶� ����
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
	// ����Ʈ�� �Ҽӵ� ���͸� ��ȸ�ϸ� ������Ʈ�� �����Ų��.

	// Transform ������Ʈ ��ȸ
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

	// �Ϲ� ������Ʈ ��ȸ
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
	// ����̽��� RenderStart() �� ���� ����� ����Ÿ���� Ŭ���� �� �¾����ش�.
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


	// ������ ����Ʈ �ڷ���� ���� Render() �� �����Ѵ�.
	for (std::pair<int, std::list<GameEngineRenderer*>> Pair : RendererList_)
	{
		std::list<GameEngineRenderer*>& Renderers = Pair.second;
		// ���� ī�޶��� ����İ� ���� ����� �����´�.
		float4x4 View = MainCameraActor_->GetViewMatrix();
		float4x4 Porjection = MainCameraActor_->GetPorjectionMatrix();

		for (GameEngineRenderer* Renderer : Renderers)
		{
			if (false == Renderer->IsUpdate())
			{
				// Ȱ��ȭ�� �Ǿ� ���� ���� �������� �н�
				continue;
			}

			// �������� ���� �� ����İ� ���� ��İ��� �־� �ش�.
			Renderer->GetTransform()->GetTransformData().Projection_ = Porjection;
			Renderer->GetTransform()->GetTransformData().View_ = View;

			// �ϼ��� �������� ���������ش�
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