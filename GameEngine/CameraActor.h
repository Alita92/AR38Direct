#pragma once
#include "GameEngineActor.h"

class CameraComponent;
// 설명 :
class CameraActor : public GameEngineActor // Actor 상속받는다.
{
public:
	// constrcuter destructer
	CameraActor();
	~CameraActor();

	// delete Function
	CameraActor(const CameraActor& _Other) = delete;
	CameraActor(CameraActor&& _Other) noexcept = delete;
	CameraActor& operator=(const CameraActor& _Other) = delete;
	CameraActor& operator=(CameraActor&& _Other) noexcept = delete;

	CameraComponent* GetCamera()
	{
		return Camera_;
	}

	float4x4 GetViewMatrix();
	float4x4 GetPorjectionMatrix();

protected:
	virtual void Start();
	virtual void TransformUpdate();
	virtual void Update(float _DeltaTime);

private:
	CameraComponent* Camera_;
	// 카메라 컴포넌트를 멤버로 보유한다.
};

