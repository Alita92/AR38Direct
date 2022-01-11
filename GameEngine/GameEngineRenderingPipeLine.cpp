#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() // default constructer ����Ʈ ������
{

}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void GameEngineRenderingPipeLine::SetInputAssembler1(GameEngineVertexBuffer* _Ptr) // ���� ���� �Է°��� �޾� ��
{
	VertexBuffer_ = _Ptr;
}

void GameEngineRenderingPipeLine::SetVertexShader(GameEngineVertexShader* _Ptr) // ���� ���̴� �Է°��� �޾� ��
{
	VertexShader_ = _Ptr;
}


void GameEngineRenderingPipeLine::Rendering() // ���ؽ� ī�� �ǽ�
{
	// input����� �ܰ�
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