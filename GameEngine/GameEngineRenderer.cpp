#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineTransform.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "CameraComponent.h"

GameEngineRenderer::GameEngineRenderer()
	: PipeLine_(nullptr)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}


void GameEngineRenderer::Render()
{
	ShaderHelper.Setting();
	PipeLine_->Rendering();
	ShaderHelper.ReSet();
	PipeLine_->Reset();
}


void GameEngineRenderer::SetRenderingPipeLine(const std::string& _Value)
{
	PipeLine_ = GameEngineRenderingPipeLineManager::GetInst().Find(_Value);

	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 랜더링 파이프라인입니다." + _Value);
	}

	ShaderHelper.ShaderResourcesCheck(PipeLine_->GetVertexShader());
	ShaderHelper.ShaderResourcesCheck(PipeLine_->GetPixelShader());

	if (true == ShaderHelper.IsConstantBuffer("TransformData"))
	{
		ShaderHelper.SettingConstantBufferLink("TransformData", GetTransform()->GetTransformData());
	}

	if (nullptr == PipeLine_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 파이프라인 입니다!");
	}
}

void GameEngineRenderer::Start()
{
	// 메인 카메라에 이걸 렌더링할 목록에 넣어 줘... 하는 것
	GetLevel()->GetMainCamera()->PushRenderer(GetOrder(), this);
}

void GameEngineRenderer::Update()
{

}