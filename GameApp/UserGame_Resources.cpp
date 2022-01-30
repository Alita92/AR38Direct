#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"


void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("AR38Direct");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}


	{
		// 각자 물체가 각자의 크기와 회전값을 가진 세상
		// 로컬스페이스

		// 로컬세상에 있는 물체를 우리가 원하는 대로 변형하고
		// 위치시키고 인식합니다.
		// 월드스페이스

		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		{
			// 앞면
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.5f }) };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.5f }) };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.5f }) };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.5f }) };

			RectVertex[4] = { float4::RotateXDegree(RectVertex[0].Postion, 180.0f) };
			RectVertex[5] = { float4::RotateXDegree(RectVertex[1].Postion, 180.0f) };
			RectVertex[6] = { float4::RotateXDegree(RectVertex[2].Postion, 180.0f) };
			RectVertex[7] = { float4::RotateXDegree(RectVertex[3].Postion, 180.0f) };
		}

		{
			RectVertex[8] = { float4::RotateYDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[9] = { float4::RotateYDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[10] = { float4::RotateYDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[11] = { float4::RotateYDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[12] = { float4::RotateYDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[13] = { float4::RotateYDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[14] = { float4::RotateYDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[15] = { float4::RotateYDegree(RectVertex[3].Postion, -90.0f) };
		}

		{
			RectVertex[16] = { float4::RotateXDegree(RectVertex[0].Postion, 90.0f) };
			RectVertex[17] = { float4::RotateXDegree(RectVertex[1].Postion, 90.0f) };
			RectVertex[18] = { float4::RotateXDegree(RectVertex[2].Postion, 90.0f) };
			RectVertex[19] = { float4::RotateXDegree(RectVertex[3].Postion, 90.0f) };

			RectVertex[20] = { float4::RotateXDegree(RectVertex[0].Postion, -90.0f) };
			RectVertex[21] = { float4::RotateXDegree(RectVertex[1].Postion, -90.0f) };
			RectVertex[22] = { float4::RotateXDegree(RectVertex[2].Postion, -90.0f) };
			RectVertex[23] = { float4::RotateXDegree(RectVertex[3].Postion, -90.0f) };
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		for (int i = 0; i < 6; i++)
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	// 이걸 그래픽 카드에게 알려주는 겁니다.
	{

		// POSITION을 시맨틱이라고 합니다.
		// 
		std::string ShaderCode =
			"\
			float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Create("StartVertexShader", ShaderCode);

		Ptr->AddInputLayOut("TEXCOORD", 0, 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		Ptr->AddInputLayOut("POSTION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		Ptr->AddInputLayOut("COLOR", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);

	}

	{
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("TestReasterizer");
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");
		//Pipe->SetInputAssembler1();
	}



}
