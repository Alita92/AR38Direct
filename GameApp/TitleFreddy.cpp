#include "PreCompile.h"
#include "TitleFreddy.h"

#include <GameEngine/GameEngineImageRenderer.h>

TitleFreddy::TitleFreddy() // default constructer ����Ʈ ������
	: titleFreddyImageRenderer_(nullptr)
{

}

TitleFreddy::~TitleFreddy() // default destructer ����Ʈ �Ҹ���
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