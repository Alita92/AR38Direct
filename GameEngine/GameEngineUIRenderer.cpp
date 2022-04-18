#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"


int GameEngineUIRenderer::UIRendererCount = 0;

GameEngineUIRenderer::GameEngineUIRenderer()
{
	++UIRendererCount;
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
	--UIRendererCount;
}
void GameEngineUIRenderer::Start()
{
	// Push Render¸¦ ¸Þ
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
	SetRenderingPipeLine("TextureUI");
	ImageRendererStart();

}





void GameEngineUIRenderer::SetRenderGroup(int _Order)
{
	GetLevel()->GetUICamera()->ChangeRendererGroup(_Order, this);;
}