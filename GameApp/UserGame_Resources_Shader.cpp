#include "Precompile.h"
#include "UserGame_Resources_Shader.h"

void AppShaderLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParent("AR38Direct");
	Dir.MoveChild("Resources");
	Dir.MoveChild("Shader");

	std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");
	// fx 파일을 모두 가져와 벡터자료형에 수집한다

	for (auto& ShaderFile : AllShader)
	{
		ShaderFile.Open("rt");

		std::string FileName = ShaderFile.GetFileNameWithOutExtension();
		std::string AllCode = ShaderFile.GetString();

		if (std::string::npos != AllCode.find(FileName + "_VS"))
		{
			GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create(FileName + "_VS", AllCode);
		}

		if (std::string::npos != AllCode.find(FileName + "_PS"))
		{
			GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create(FileName + "_PS", AllCode);
		}

	}


	{
		// Color.fx
		// 이제 이런거들을 for 돌면서 모두 실행되고 밑의 모든 걸 대체할 것...

		std::string ShaderCode =
			"\
			float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

		//Ptr->AddInputLayOut("TEXCOORD", 0, 0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	}

	{

		// 도화지가 한장 대져있죠?
		std::string ShaderCode =
			"\
			float4 StartPixelShader( float4 pos : SV_POSITION ) : SV_Target0\n \
			{\n \
				return float4(1.0f, 0.0f, 0.0f, 1.0f);\n\
			}\n\
			";

		GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Create("StartPixelShader", ShaderCode);
	}


}