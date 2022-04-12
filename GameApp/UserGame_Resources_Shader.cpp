#include "Precompile.h"
#include "UserGame_Resources_Shader.h"


// 셰이더 폴더 내의 모든 fx 셰이더코드를 가져오는 역할을 합니다.
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
		// 오픈모드
		// rt : 텍스트 파일로 읽어들인다
	
		std::string FileName = ShaderFile.GetFileNameWithOutExtension();
		std::string AllCode = ShaderFile.GetString(); // 파일 내의 모든 텍스트를 가져온다.
	
		if (std::string::npos != AllCode.find(FileName + "_VS")) // npos = -1 로 정의된 특수값, "find() 값을 못 찾을시 npos 리턴된다!"
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