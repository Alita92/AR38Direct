#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
	: Parent_(nullptr)
{
}

GameEngineTransform::~GameEngineTransform()
{
}

void GameEngineTransform::TransformUpdate()
{
	TransData_.LocalCalculation();
	// 로컬 크자이를 곱연산해 월드 행렬을 구성하고...


	// TransData_.LocalWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	// TransData_.WorldWorld_;
	// [][][][]
	// [][][][]
	// [][][][]
	// [][][][]

	if (nullptr != Parent_)
	{	
		// 부모가 있다면 그 행렬 데이터에 부모의 기본 행렬을 곱연산해준다.
		TransData_.ParentSetting(Parent_->TransData_.WorldWorld_);
	}
	else {
		// 아니면 자식만 있는 단일 개체로, 로컬이 곧 월드로 바로 가게끔 계산해준다.
		TransData_.RootCalculation();
	}

}

void GameEngineTransform::AllChildCalculationScaling()
{	// 자식들을 전부 순회하며 다 크기를 키워 준다.
	for (auto& Child : Childs_)
	{
		// 부모의 크기가 바뀐것이고 부모의 크기가 바뀌었다는것은
		// 자식의 월드 포지션이 바뀌었다는것을 의미한다.

		// 즉 자식들의 Scaling 에는 필히 Position 역시 계산해주어야 한다.
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();

		Child->AllChildCalculationScaling();
		// 자식의 자식들에게 재귀함수로 들어갈 수 있도록...
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	for (auto& Child : Childs_)
	{
		// 
		Child->CalculationWorldRotation();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationRotation();
	}
}

void GameEngineTransform::AllChildCalculationPosition()
{
	for (auto& Child : Childs_)
	{
		Child->CalculationWorldPosition();
		Child->AllChildCalculationPosition();
	}
}

void GameEngineTransform::CalculationWorldScaling()
{
	// 자식의 크기값에 부모의 기본 크기값을 곱해 준다.
	TransData_.vWorldScaling_ = Parent_->TransData_.vWorldScaling_ * TransData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalScaling()
{
	// 역 스케일링
	TransData_.vLocalScaling_ = TransData_.vWorldScaling_ / Parent_->TransData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	// 자식의 회전각도에 부모의 회전각도를 더해 준다.
	TransData_.vWorldRotation_ = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	// 역 스케일링
	TransData_.vLocalRotation_ = TransData_.vWorldRotation_ - Parent_->TransData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	// TransData_.v = Parent_->TransData_.vWorldRotation_ + TransData_.vLocalRotation_;
}


void GameEngineTransform::CalculationWorldPosition()
{
	// 원점기준으로의 나의 포지션 무
	float4 CalLocalPos = TransData_.vLocalPosition_;

	// 크기를 키우고
	CalLocalPos *= Parent_->TransData_.vWorldScaling_;

	// 회전시키고
	CalLocalPos.Rotate3DDegree(Parent_->TransData_.vWorldRotation_);

	// 부모의 위치를 더해준 게
	CalLocalPos += Parent_->TransData_.vWorldPosition_;

	// 월드값으로 환산한 포지션
	TransData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransData_.vLocalScaling_ = _Value;
	CalculationWorldScaling();
	AllChildCalculationScaling();
}



void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalScaling_ = _Value;
		TransData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		return;
	}

	TransData_.vWorldScaling_ = _Value;
	CalculationLocalScaling();
	AllChildCalculationScaling();
}

// 무모건 디그리
void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vLocalRotation_ = _Value;
	CalculationWorldRotation();
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalRotation_ = _Value;
		TransData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();
}


void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransData_.vLocalPosition_ = _Value;
		TransData_.vLocalPosition_ = _Value;
		AllChildCalculationRotation();
		return;
	}

	TransData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value) {

}

void GameEngineTransform::DetachChild(GameEngineTransform* _Child)
{
	Childs_.remove(_Child);
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	// 나는 이제부터 _Parent를 따라다녀야 합니다.

	if (nullptr != Parent_)
	{
		Parent_->DetachChild(this);
	}

	Parent_ = _Parent;
	_Parent->Childs_.push_back(this);
}