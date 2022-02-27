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


	// GameEngineVertexShaderManager::GetInst().Load(Dir.PathToPlusFileName("Color.fx"), "Color_VS");

	//{
	//	// Color.fx

	//	std::string ShaderCode =
	//		"\
	//		float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
	//		{\n \
	//			return pos;\n\
	//		}\n\
	//		";

	//	GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

	//	//Ptr->AddInputLayOut("TEXCOORD", 0, 0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//	//Ptr->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//	//Ptr->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	//}

	//{

	//	// 도화지가 한장 대져있죠?
	//	std::string ShaderCode =
	//		"\
	//		float4 StartPixelShader( float4 pos : SV_POSITION ) : SV_Target0\n \
	//		{\n \
	//			return float4(1.0f, 0.0f, 0.0f, 1.0f);\n\
	//		}\n\
	//		";

	//	GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create("StartPixelShader", ShaderCode);
	//}


}