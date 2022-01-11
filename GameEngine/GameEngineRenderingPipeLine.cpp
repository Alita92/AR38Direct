#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer 디폴트 생성자
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer 디폴트 소멸자
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(GameEngineVertexBuffer* _Ptr) // 그저 버퍼 입력값을 받아 줆
{
	VertexBuffer_ = _Ptr;
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Ptr) // 그저 쉐이더 입력값을 받아 줆
{
	VertexShader_ = _Ptr;
}


void GameEngineRenderingPipeLine::Rendering() // 버텍스 카피 실시
{
	// input어셈블러 단계
	std::vector<float4> CopyVertex;
	{
		CopyVertex = VertexBuffer_->GetVertexs();
	}

	{
		for (size_t i = 0; i < CopyVertex.size(); i++)
		{
			CopyVertex[i] = VertexShader_->VertexShaderFunction(CopyVertex[i]);
		}

		// 
	}
}