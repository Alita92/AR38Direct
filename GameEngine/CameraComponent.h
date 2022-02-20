	#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"

enum class ProjectionMode
{
	Perspective,
	Orthographic
};

// ���� :
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
	ProjectionMode ProjectionMode_; // ���� ����Ǵ� ���� ��Ÿ��(����/����)
	float FovAngleY_; // Y�� �þ߰�
	float4 CamSize_; // ī�޶��� ũ��(��ũ�� �ػ󵵰� ����)
	float NearZ_; // �ּ� ���ðŸ�
	float FarZ_; // �ִ� ���ðŸ�



	void CameraTransformUpdate();
};

