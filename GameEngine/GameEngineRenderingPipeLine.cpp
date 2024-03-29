#include "PreCompile.h"
#include "GameEngineResourcesManager.h"



#include "GameEngineWindow.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer 디폴트 생성자
	: VertexBuffer_(nullptr)
	, InputLayOutVertexShader_(nullptr)
	, VertexShader_(nullptr)
	, IndexBuffer_(nullptr)
	, Topology_(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	// 나에게 메모 : 기본 값을 일괄적으로 미리 설정해논 부분임.
	// 이 외의 블렌드, 레스터라이저, 깊이 버퍼 스텐실과 토폴로지 설정시
	// 리소스 코드에서 직접 바꿔줘야 함...

	SetOutputMergerBlend("AlphaBlend");
	SetRasterizer("EngineBaseRasterizer");
	SetOutputMergerDepthStencil("BaseDepthOn");
	SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: VertexBuffer_(_other.VertexBuffer_)
	, VertexShader_(_other.VertexShader_)
	, IndexBuffer_(_other.IndexBuffer_)
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBufferSetting(const std::string& _Name)
{
	VertexBuffer_ = GameEngineVertexBufferManager::GetInst().Find(_Name);

	if (nullptr == VertexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}

}

void GameEngineRenderingPipeLine::SetInputAssembler1InputLayOutSetting(const std::string& _Name)
{
	InputLayOutVertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == InputLayOutVertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBufferSetting(const std::string& _Name)
{
	IndexBuffer_ = GameEngineIndexBufferManager::GetInst().Find(_Name);

	if (nullptr == IndexBuffer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 버퍼를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	Topology_ = _Topology;
}


void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader_ = GameEngineVertexShaderManager::GetInst().Find(_Name);

	if (nullptr == VertexShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer_ = GameEngineRasterizerManager::GetInst().Find(_Name);

	if (nullptr == Rasterizer_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 레이터라이저 세팅을 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader_ = GameEnginePixelShaderManager::GetInst().Find(_Name);

	if (nullptr == PixelShader_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 픽셀 쉐이더를 세팅을 세팅하려고 했습니다.");
		return;
	}


}

void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend_ = GameEngineBlendManager::GetInst().Find(_Name);

	if (nullptr == Blend_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 블랜드 세팅을 세팅하려고 했습니다.");
		return;
	}

}

void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil_ = GameEngineDepthStencilManager::GetInst().Find(_Name);
	if (nullptr == DepthStencil_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 깊이 세팅을 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::InputAssembler1()
{
	VertexBuffer_->Setting();
	InputLayOutVertexShader_->InputLayOutSetting();
}

void GameEngineRenderingPipeLine::InputAssembler2()
{
	IndexBuffer_->Setting();
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology_);
}

void GameEngineRenderingPipeLine::VertexShader()
{
	VertexShader_->Setting();
}

void GameEngineRenderingPipeLine::Rasterizer()
{
	Rasterizer_->Setting();
	Rasterizer_->SettingViewPort();
}


void GameEngineRenderingPipeLine::PixelShader()
{
	PixelShader_->Setting();
}

void GameEngineRenderingPipeLine::OutputMerger()
{
	Blend_->Setting();
	DepthStencil_->Setting();
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	// input어셈블러 단계
	InputAssembler1();

	InputAssembler2();

	VertexShader();

	Rasterizer();

	PixelShader();

	OutputMerger();
}

void GameEngineRenderingPipeLine::Rendering()
{
	RenderingPipeLineSetting();

	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer_->GetIndexCount(), 0, 0);
	// drawindexed : 인덱싱된 버퍼들을 그리는 함수.
	// 해당 렌더링 파이프라인의 버텍스 -> 인덱스 형식에 맞춰 렌더링을 실행한다.
}


void GameEngineRenderingPipeLine::Reset()
{
	Blend_->Reset();
	DepthStencil_->Reset();
}