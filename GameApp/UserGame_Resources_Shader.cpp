#include "Precompile.h"
#include "UserGame_Resources_Shader.h"


// ���̴� ���� ���� ��� fx ���̴��ڵ带 �������� ������ �մϴ�.
// 
void AppShaderLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParent("AR38Direct");
	Dir.MoveChild("Resources");
	Dir.MoveChild("Shader");
	
	std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");
	
	for (auto& ShaderFile : AllShader)
	{
		ShaderFile.Open("rt");
		// ���¸��
		// rt : �ؽ�Ʈ ���Ϸ� �о���δ�
	
		std::string FileName = ShaderFile.GetFileNameWithOutExtension();
		std::string AllCode = ShaderFile.GetString(); // ���� ���� ��� �ؽ�Ʈ�� �����´�.
	
		if (std::string::npos != AllCode.find(FileName + "_VS")) // npos = -1 �� ���ǵ� Ư����, "find() ���� �� ã���� npos ���ϵȴ�!"
		{
			GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
		}
	
		if (std::string::npos != AllCode.find(FileName + "_PS"))
		{
			GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
		}
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Curved");
		Pipe->SetInputAssembler1VertexBufferSetting("FullRect");
		Pipe->SetInputAssembler1InputLayOutSetting("Curved_VS");
		Pipe->SetVertexShader("Curved_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("FullRect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetOutputMergerDepthStencil("MergeDepth");
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Curved_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}


}