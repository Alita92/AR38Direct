#include "PreCompile.h"
#include "GameEngineTransform.h"
#include "CameraComponent.h"
#include "GameEngineWindow.h"

CameraComponent::CameraComponent()
	: ProjectionMode_(ProjectionMode::Perspective)
	, FovAngleY_(90.0f)
	, CamSize_(GameEngineWindow::GetInst().GetSize())
	, NearZ_(0.1f)
	, FarZ_(1000.0f)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Start()
{

}



void CameraComponent::Update()
{
}

void CameraComponent::CameraTransformUpdate()
{
	GetTransform()->GetTransformData().View_.ViewToLH(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldForwardVector(), GetTransform()->GetWorldUpVector());
	// 트랜스폼의 뷰행렬을 가져오고, ViewToLH() 로 바라보는 위치를 정의한다.

	switch (ProjectionMode_) // 설정한 투영 스타일에 따라 마지막에 다른 계산을 내린다
	{
	case ProjectionMode::Perspective:
		GetTransform()->GetTransformData().Projection_.PerspectiveFovLH(FovAngleY_, CamSize_.x, CamSize_.y, NearZ_, FarZ_);
		break;
	case ProjectionMode::Orthographic:
		GetTransform()->GetTransformData().Projection_.OrthographicLH(CamSize_.x, CamSize_.y, NearZ_, FarZ_);
		break;
	default:
		break;
	}
}