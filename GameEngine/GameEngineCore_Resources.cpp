#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineCollision.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDepthStencil.h"
#include "EngineVertex.h"


void GameEngineCore::EngineResourcesLoad()
{
	{
		GameEngineDirectory EngineTextureDir;
		EngineTextureDir.MoveParent("AR38Direct");
		EngineTextureDir.MoveChild("EngineResources");
		EngineTextureDir.MoveChild("Texture");

		std::vector<GameEngineFile> AllFile = EngineTextureDir.GetAllFile();

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParent("AR38Direct");
		Dir.MoveChild("EngineResources");
		Dir.MoveChild("Shader");

		std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");

		for (auto& ShaderFile : AllShader)
		{
			ShaderFile.Open("rt");

			std::string FileName = ShaderFile.GetFileNameWithOutExtension();
			std::string AllCode = ShaderFile.GetString();

			if (std::string::npos != AllCode.find(FileName + "_VS"))
			{
				GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
			}

			if (std::string::npos != AllCode.find(FileName + "_PS"))
			{
				GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
			}

		}
	}


	// 라이너가 아닌 포인터 설정을 적용한 샘플러를 만들려면 이렇게 임의로 해 줘야 합니다.
	// 샘플러 생성 시 기본 값은 어디까지나 라이너이기 때문에...
	//GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().Find("PointSmp");
	//NewRes->Info_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//NewRes->ReCreate();


}
void GameEngineCore::EngineResourcesCreate()
{

	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		{
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

		for (size_t i = 0; i < RectVertex.size(); i += 4)
		{
			RectVertex[i + 0].Texcoord = { 0.0f, 0.0f };
			RectVertex[i + 1].Texcoord = { 1.0f, 0.0f };
			RectVertex[i + 2].Texcoord = { 1.0f, 1.0f };
			RectVertex[i + 3].Texcoord = { 0.0f, 1.0f };
		}

		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
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

		GameEngineIndexBufferManager::GetInst().Create("Box", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}



	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		{
			// 앞면
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(5);

		{
			// 앞면
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };
			RectVertex[4] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
		}

		GameEngineVertexBufferManager::GetInst().Create("DebugRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);
		RectIndex.push_back(3);
		RectIndex.push_back(4);

		GameEngineIndexBufferManager::GetInst().Create("DebugRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		{
			// 앞면
			RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }),float4({ 0.0f, 0.0f }) };
			RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }), float4({ 1.0f, 0.0f }) };
			RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }), float4({ 1.0f, 1.0f }) };
			RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }),  float4({ 0.0f, 1.0f }) };
		}

		GameEngineVertexBufferManager::GetInst().Create("FullRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("FullRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	// 오피스 반원통형 렌더링

	{
		std::vector<GameEngineVertex> HalfCylinderVertex = std::vector<GameEngineVertex>(4 * 8);

		{
			HalfCylinderVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[1] = { float4({ -0.375f, 0.5f, 0.0f }),  { 0.125f, 0.0f } };
			HalfCylinderVertex[2] = { float4({ -0.375f, -0.5f, 0.0f }),  { 0.125f, 1.0f } };
			HalfCylinderVertex[3] = { float4({ -0.5f, -0.5f, 0.5f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[4] = { float4({-0.375f, 0.5f, 0.0f}),  {0.125f, 0.0f}};
			HalfCylinderVertex[5] = { float4({ -0.25f, 0.5f, 0.0f}),  {0.25f, 0.0f} };
			HalfCylinderVertex[6] = { float4({-0.25f, -0.5f, 0.0f}),  {0.25f, 1.0f}};
			HalfCylinderVertex[7] = { float4({-0.375f, -0.5f, 0.0f}), {0.125f, 1.0f}};

			HalfCylinderVertex[8] = { float4({ -0.25f, 0.5f, 0.0f }),  { 0.25f, 0.0f } };
			HalfCylinderVertex[9] = { float4({ -0.125f, 0.5f, 0.0f }),  { 0.375f, 0.0f } };
			HalfCylinderVertex[10] = { float4({ -0.125f, -0.5f, 0.0f }),  { 0.375f, 1.0f } };
			HalfCylinderVertex[11] = { float4({ -0.25f, -0.5f, 0.0f }),  { 0.25f, 1.0f } };

			// 중앙
			HalfCylinderVertex[12] = { float4({ -0.125f, 0.5f, 0.0f }),  { 0.375f, 0.0f } };
			HalfCylinderVertex[13] = { float4({ 0.0f, 0.5f, 0.0f }),  { 0.5f, 0.0f } };
			HalfCylinderVertex[14] = { float4({ 0.0f, -0.5f, 0.0f }),  { 0.5f, 1.0f } };
			HalfCylinderVertex[15] = { float4({ -0.125f, -0.5f, 0.0f }),  { 0.375f, 1.0f } };

			HalfCylinderVertex[16] = { float4({ 0.0f, 0.5f, 0.0f }),  { 0.5f, 0.0f } };
			HalfCylinderVertex[17] = { float4({ 0.125f, 0.5f, 0.0f }),  { 0.625f, 0.0f } };
			HalfCylinderVertex[18] = { float4({ 0.125f, -0.5f, 0.0f }),  { 0.625f, 1.0f } };
			HalfCylinderVertex[19] = { float4({ 0.0f, -0.5f, 0.0f }),  { 0.5f, 1.0f } };
			// 중앙 끝

			HalfCylinderVertex[20] = { float4({ 0.125f, 0.5f, 0.0f }),  { 0.625f, 0.0f } };
			HalfCylinderVertex[21] = { float4({ 0.25f, 0.5f, 0.0f }),  { 0.75f, 0.0f } };
			HalfCylinderVertex[22] = { float4({ 0.25f, -0.5f, 0.0f }),  { 0.75f, 1.0f } };
			HalfCylinderVertex[23] = { float4({ 0.125f, -0.5f, 0.0f }),  { 0.625f, 1.0f } };

			HalfCylinderVertex[24] = { float4({ 0.25f, 0.5f, 0.0f }),  { 0.75f, 0.0f } };
			HalfCylinderVertex[25] = { float4({ 0.375f, 0.5f, 0.0f }),  { 0.875f, 0.0f } };
			HalfCylinderVertex[26] = { float4({ 0.375f, -0.5f, 0.0f }),  { 0.875f, 1.0f } };
			HalfCylinderVertex[27] = { float4({ 0.25f, -0.5f, 0.0f }),  { 0.75f, 1.0f } };

			HalfCylinderVertex[28] = { float4({ 0.375f, 0.5f, 0.0f }),  { 0.875f, 0.0f } };
			HalfCylinderVertex[29] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[30] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[31] = { float4({ 0.375f, -0.5f,0.0f }),  { 0.875f, 1.0f } };
		}

		GameEngineVertexBufferManager::GetInst().Create("HalfCylinder", HalfCylinderVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<UINT> HalfCylinderIndex;

		for (int i = 0; i < 8; i++)
		{
			HalfCylinderIndex.push_back(i * 4 + 0);
			HalfCylinderIndex.push_back(i * 4 + 1);
			HalfCylinderIndex.push_back(i * 4 + 2);

			HalfCylinderIndex.push_back(i * 4 + 0);
			HalfCylinderIndex.push_back(i * 4 + 2);
			HalfCylinderIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("HalfCylinder", HalfCylinderIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}



	{
		D3D11_RASTERIZER_DESC Info = { D3D11_FILL_MODE::D3D11_FILL_SOLID, };
		Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//D3D11_FILL_SOLID;
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Info.AntialiasedLineEnable = true;
		Info.MultisampleEnable = false;
		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	{
		D3D11_BLEND_DESC BlendInfo = { 0 };

		BlendInfo.AlphaToCoverageEnable = FALSE;
		BlendInfo.IndependentBlendEnable = FALSE;
		BlendInfo.RenderTarget[0].BlendEnable = true;
		BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlendManager::GetInst().Create("AlphaBlend", BlendInfo);
	}


	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = true;
		DepthInfo.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		DepthInfo.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthInfo.StencilEnable = false;
		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOn", DepthInfo);
	}

	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = true;
		DepthInfo.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		DepthInfo.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		DepthInfo.StencilEnable = false;
		GameEngineDepthStencilManager::GetInst().Create("MergeDepth", DepthInfo);
	}


	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = false;
		DepthInfo.StencilEnable = false;
		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOff", DepthInfo);
	}



	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("DebugRect");
		Pipe->SetInputAssembler1VertexBufferSetting("DebugRect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("DebugRect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Pipe->SetPixelShader("Color_PS");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TargetMerge");
		Pipe->SetInputAssembler1VertexBufferSetting("FullRect");
		Pipe->SetInputAssembler2IndexBufferSetting("FullRect");
		Pipe->SetInputAssembler1InputLayOutSetting("TargetMerge_VS");
		Pipe->SetVertexShader("TargetMerge_VS");
		Pipe->SetPixelShader("TargetMerge_PS");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}


	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TextureUI");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}

}