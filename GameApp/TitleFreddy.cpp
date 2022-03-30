#include "PreCompile.h"
#include "TitleFreddy.h"
#include "ENUM.h"

#include <GameEngine/GameEngineImageRenderer.h>

TitleFreddy::TitleFreddy() // default constructer 디폴트 생성자
	: titleFreddyImageRenderer_(nullptr), generalInterTime_(0.0f), facialChangeInterTime_(0.0f), isFirstSessionOut_(false), timeDice_(0), faceDice_(0), isGameStarted_(false)
{

}

TitleFreddy::~TitleFreddy() // default destructer 디폴트 소멸자
{

}

void TitleFreddy::Start()
{
	GetTransform()->SetWorldPosition({ 0.f,0.f,0.f });

	titleFreddyImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleFreddyImageRenderer_->SetImage("TitleFreddy_0.png", true);
	titleFreddyImageRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1)});
}

void TitleFreddy::Update(float _Deltatime)
{
	if (false == isGameStarted_)
	{
		FreddyFacialChange();
	}
}

void TitleFreddy::FreddyFacialChange()
{
	generalInterTime_ += GameEngineTime::GetInst().GetDeltaTime();
	// 초반 3초간은 표정이 변하지 않게 bool 로 체크해줍니다.
	if (false == isFirstSessionOut_ && 8.0f <= generalInterTime_)
	{
		timeDice_ = randomGenerator_.RandomInt(0, 3);
		faceDice_ = randomGenerator_.RandomInt(0, 3);
		generalInterTime_ = 0.0f;
		isFirstSessionOut_ = true;
		return;
	}


	switch (timeDice_)
	{
	case 0 :
		if (0.5f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 1:
		if (1.0f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 2:
		if (1.5f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	case 3:
		if (2.0f <= generalInterTime_)
		{
			RandomImageChange();
		}
		break;
	default:
		break;
	}
	
	return;
}

void TitleFreddy::RandomImageChange()
{
	facialChangeInterTime_ += GameEngineTime::GetInst().GetDeltaTime();

	switch (faceDice_)
	{
	case 0:
		titleFreddyImageRenderer_->SetImage("TitleFreddy_1.png", true);
		break;
	case 1:
		titleFreddyImageRenderer_->SetImage("TitleFreddy_2.png", true);
		break;
	case 2:
		titleFreddyImageRenderer_->SetImage("TitleFreddy_3.png", true);
		break;
	default:
		break;
	}

	if (0.1f <= facialChangeInterTime_)
	{
		// 마무리 초기화
		faceDice_ = randomGenerator_.RandomInt(0, 2);
		timeDice_ = randomGenerator_.RandomInt(0, 3);
		generalInterTime_ = 0.0f;
		facialChangeInterTime_ = 0.0f;
		
		switch (randomGenerator_.RandomInt(0,2))
		{
		case 0:
		case 1:
			titleFreddyImageRenderer_->SetImage("TitleFreddy_0.png", true);
			break;
		case 2:
			titleFreddyImageRenderer_->SetImage("TitleFreddy_4.png", true);
			break;
		default:
			break;
		}

		return;
	}
}