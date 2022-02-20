#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}


void GameEngineRenderer::Render()
{
	// 세팅한 파이프라인의 렌더링을 여기서 돌린다!
	PipeLine_->Rendering();
}


void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find("Color");

	if (true == PipeLine_->ShaderHelper.IsConstantBuffer("TransformData"))
	{
		PipeLine_->ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
	}

	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 파이프라인 입니다!");
	}
}

void GameEngineRenderer::Start()
{	
	// 렌더러가 컴포넌트로 "만들어질 시" 렌더러를 푸시백 해 준다.
	GetLevel()->PushRenderer(GetOrder(), this);
}
void GameEngineRenderer::Update()
{

}