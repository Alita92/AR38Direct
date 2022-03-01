#include "PreCompile.h"
#include "TitleFreddy.h"

#include <GameEngine/GameEngineImageRenderer.h>

TitleFreddy::TitleFreddy() // default constructer 디폴트 생성자
	: titleFreddyImageRenderer_(nullptr)
{

}

TitleFreddy::~TitleFreddy() // default destructer 디폴트 소멸자
{

}

void TitleFreddy::Start()
{
	titleFreddyImageRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	titleFreddyImageRenderer_->SetImage("TitleFreddy_0.png", true);
}

void TitleFreddy::Update(float _Deltatime)
{

}