#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine/EngineVertex.h>
#include "UserGame_Resources_Shader.h"


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
			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}


	{
	//	GameEngineDirectory TextureDir;
	//	TextureDir.MoveParent("AR38Direct");
	//	TextureDir.MoveChild("Resources");
	//	TextureDir.MoveChild("Image");
	//
	//	std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();
	//	
	//	for (size_t i = 0; i < AllFile.size(); i++)
	//	{
	//		// 가져온 모든 리소스를 for 로 타고 다니며 모두 텍스처로 Load 해 준다.
	//		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
	//	}
	}

	AppShaderLoad();




	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");

		// 이런 기본적인 vertex들이 있다.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");

		// 그 vertex을 이렇게 위치시키겠다.
		Pipe->SetVertexShader("Color_VS");

		// 그 vertex을 3개 묶어서 면으로 그리겠다. 순서는 인덱스 버퍼의 순서대로
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 헐 테셀레이션 도메인 지오메트리는 있으면 적용되고 없어도 필수는 아니다. 
		// vertex을 더 쪼갤건데 준비를 하겠다. 
		// 헐
		// 
		// 헐에서 정한대로 vertex를 더 쪼갠다.
		// 테셀레이션 
		// 
		// 그 더 쪼갠 vertex들을 수정하겠다.
		// 도메인 
		// 
		// 지오메트리 완전히 새로운 vertex들을 또 만들겠다.
		// 애는 게임에서 좀 많이 쓸모있음.

		// 그리리기한 면혹은 선 등등에 겹치는 모니터의 픽셀들을 추출하겠다. 
		// 레스터라이터라이저
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}



	{
		// 현재 이미지 파일의 렌더링을 돌리는 파이프라인입니다. (플레이어, 몬스터)
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
}
