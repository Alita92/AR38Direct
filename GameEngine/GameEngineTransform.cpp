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
	// 행렬을 업데이트? 해 준다?
	TransformData_.LocalCalculation();
	//void LocalCalculation()
	//{
	//	LocalScaling_.Scaling(vLocalScaling_);
	//	LocalRotation_.RotationDeg(vLocalRotation_);
	//	LocalPosition_.Translation(vLocalPosition_);
	//
	//	LocalWorld_ = LocalScaling_ * LocalRotation_ * LocalPosition_;
	//} <= 이런 식으로...


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

	if (nullptr != Parent_) // 부모 액터가 있다면
	{
		TransformData_.ParentSetting(Parent_->TransformData_.WorldWorld_);
		// 자신의 로컬에 부모의 월드값을 곱연산해준다
	}
	else { // 부모 액터가 없으면...
		TransformData_.RootCalculation(); 
		// 내 로컬이 곧 월드다...
	}

	// 이후에는 내 자식들의(있다면) 트랜스폼들을 재귀함수로 타고 들어가서 업데이트해준다.
	for (GameEngineTransform* ChildTransform_ : Childs_)
	{
		// 
		ChildTransform_->TransformUpdate();
	}
}

void GameEngineTransform::AllChildCalculationScaling()
{
	for (auto& Child : Childs_)
	{
		// 부모의 크기가 바뀐것이고 부모의 크기가 바뀌었다는것은
		// 자식의 월드 포지션이 바뀌었다는것을 의미한다.
		Child->CalculationWorldScaling();
		Child->CalculationWorldPosition();
		Child->AllChildCalculationScaling();
	}
}

void GameEngineTransform::AllChildCalculationRotation()
{
	for (auto& Child : Childs_)
	{
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
	TransformData_.vWorldScaling_ = Parent_->TransformData_.vWorldScaling_ * TransformData_.vLocalScaling_;
}

void GameEngineTransform::CalculationLocalScaling()
{
	TransformData_.vLocalScaling_ = TransformData_.vWorldScaling_ / Parent_->TransformData_.vWorldScaling_;
}

void GameEngineTransform::CalculationWorldRotation()
{
	TransformData_.vWorldRotation_ = Parent_->TransformData_.vWorldRotation_ + TransformData_.vLocalRotation_;
}

void GameEngineTransform::CalculationLocalRotation()
{
	TransformData_.vLocalRotation_ = TransformData_.vWorldRotation_ - Parent_->TransformData_.vWorldRotation_;
}

void GameEngineTransform::CalculationLocalPosition()
{
	float4 WorldPostion = TransformData_.vWorldPosition_ - Parent_->TransformData_.vWorldPosition_;

	WorldPostion.Rotate3DDegree(-Parent_->TransformData_.vWorldRotation_);

	WorldPostion /= Parent_->TransformData_.vWorldScaling_;

	TransformData_.vLocalPosition_ = WorldPostion;
}


void GameEngineTransform::CalculationWorldPosition()
{
	float4 CalLocalPos = TransformData_.vLocalPosition_;
	// 크기를 키우고
	CalLocalPos *= Parent_->TransformData_.vWorldScaling_;
	// 회전시키고
	CalLocalPos.Rotate3DDegree(Parent_->TransformData_.vWorldRotation_);
	// 부모의 위치로 이동한게
	CalLocalPos += Parent_->TransformData_.vWorldPosition_;

	TransformData_.vWorldPosition_ = CalLocalPos;
}

void GameEngineTransform::SetLocalScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		TransformUpdate();
		return;
	}

	TransformData_.vLocalScaling_ = _Value;
	CalculationWorldScaling();
	AllChildCalculationScaling();
	TransformUpdate();
}



void GameEngineTransform::SetWorldScaling(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalScaling_ = _Value;
		TransformData_.vWorldScaling_ = _Value;
		AllChildCalculationScaling();
		TransformUpdate();
		return;
	}

	TransformData_.vWorldScaling_ = _Value;
	CalculationLocalScaling();
	AllChildCalculationScaling();

	TransformUpdate();
}

// 무모건 디그리
void GameEngineTransform::SetLocalRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		TransformUpdate();
		return;
	}

	TransformData_.vLocalRotation_ = _Value;
	CalculationWorldRotation();
	AllChildCalculationRotation();

	TransformUpdate();
}

void GameEngineTransform::SetWorldRotation(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalRotation_ = _Value;
		TransformData_.vWorldRotation_ = _Value;
		AllChildCalculationRotation();
		TransformUpdate();
		return;
	}

	TransformData_.vWorldRotation_ = _Value;
	CalculationLocalRotation();
	AllChildCalculationRotation();

	TransformUpdate();
}


void GameEngineTransform::SetLocalPosition(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;
		AllChildCalculationPosition();
		TransformUpdate();
		return;
	}

	TransformData_.vLocalPosition_ = _Value;
	CalculationWorldPosition();
	AllChildCalculationPosition();
	TransformUpdate();
}

void GameEngineTransform::SetWorldPosition(const float4& _Value)
{
	if (nullptr == Parent_)
	{
		TransformData_.vLocalPosition_ = _Value;
		TransformData_.vWorldPosition_ = _Value;
		AllChildCalculationPosition();
		TransformUpdate();
		return;
	}

	TransformData_.vWorldPosition_ = _Value;
	CalculationLocalPosition();
	AllChildCalculationRotation();

	TransformUpdate();
}

void GameEngineTransform::DetachChildTransform(GameEngineTransform* _Transform)
{
	// 지역변수 할당을 줄이려고
	static std::vector<GameEngineTransform*>::iterator StartIter = Childs_.begin();
	static std::vector<GameEngineTransform*>::iterator EndIter = Childs_.end();

	for (; StartIter != EndIter; )
	{
		if (*StartIter != _Transform)
		{
			++StartIter;
			continue;
		}

		StartIter = Childs_.erase(StartIter);
	}

}

void GameEngineTransform::AttachTransform(GameEngineTransform* _Transform)
{
	// 나는 이제부터 _Parent를 따라다녀야 합니다.

	if (nullptr != Parent_)
	{
		Parent_->DetachChildTransform(this);
	}

	Parent_ = _Transform;
	Parent_->Childs_.push_back(this);
}

