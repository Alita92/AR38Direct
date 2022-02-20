	#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"

enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// 설명 :
class CameraComponent : public GameEngineTransformComponent
{
	friend class CameraActor;

public:
	// constrcuter destructer
	CameraComponent();
	~CameraComponent();
	CameraComponent(const CameraComponent& _Other) = delete;
	CameraComponent(CameraComponent&& _Other) noexcept = delete;
	CameraComponent& operator=(const CameraComponent& _Other) = delete;
	CameraComponent& operator=(CameraComponent&& _Other) noexcept = delete;

	void SetProjectionMode(ProjectionMode _ProjectionMode)
	{
		ProjectionMode_ = _ProjectionMode;
	}

protected:
	void Start() override;
	void Update() override;

private:
	ProjectionMode ProjectionMode_; // 현재 적용되는 투영 스타일(직교/원근)
	float FovAngleY_; // Y축 시야각
	float4 CamSize_; // 카메라의 크기(스크린 해상도가 들어간다)
	float NearZ_; // 최소 가시거리
	float FarZ_; // 최대 가시거리



	void CameraTransformUpdate();
};

