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
	//		// ������ ��� ���ҽ��� for �� Ÿ�� �ٴϸ� ��� �ؽ�ó�� Load �� �ش�.
	//		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
	//	}
	}

	AppShaderLoad();




	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");

		// �̷� �⺻���� vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayOutSetting("Color_VS");

		// �� vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("Color_VS");

		// �� vertex�� 3�� ��� ������ �׸��ڴ�. ������ �ε��� ������ �������
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// �� �׼����̼� ������ ������Ʈ���� ������ ����ǰ� ��� �ʼ��� �ƴϴ�. 
		// vertex�� �� �ɰ��ǵ� �غ� �ϰڴ�. 
		// ��
		// 
		// �濡�� ���Ѵ�� vertex�� �� �ɰ���.
		// �׼����̼� 
		// 
		// �� �� �ɰ� vertex���� �����ϰڴ�.
		// ������ 
		// 
		// ������Ʈ�� ������ ���ο� vertex���� �� ����ڴ�.
		// �ִ� ���ӿ��� �� ���� ��������.

		// �׸������� ��Ȥ�� �� �� ��ġ�� ������� �ȼ����� �����ϰڴ�. 
		// �����Ͷ����Ͷ�����
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}



	{
		// ���� �̹��� ������ �������� ������ �����������Դϴ�. (�÷��̾�, ����)
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
