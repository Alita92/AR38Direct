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

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().Load(AllFile[i].GetFullPath());
		}
	}


	{
		// Title Level
		{
			GameEngineDirectory imageDir;
			imageDir.MoveParent("AR38Direct");
			imageDir.MoveChild("Resources");
			imageDir.MoveChild("Image");
			imageDir.MoveChild("Common");

			std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

			for (size_t i = 0; i < allFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
			}
		}

		{
			GameEngineDirectory imageDir;
			imageDir.MoveParent("AR38Direct");
			imageDir.MoveChild("Resources");
			imageDir.MoveChild("Image");
			imageDir.MoveChild("Title");

			std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

			for (size_t i = 0; i < allFile.size(); i++)
			{
				GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
			}
		}
	}
	
	// Play Level
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("Play");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}

		GameEngineTexture* officeFanTexture = GameEngineTextureManager::GetInst().Find("OfficeFan.png");
		officeFanTexture->Cut(1, 3);

		GameEngineTexture* jumpScareBonnieTexture = GameEngineTextureManager::GetInst().Find("JumpScareBonnie.png");
		jumpScareBonnieTexture->Cut(1, 11);

		GameEngineTexture* LdoorTexture = GameEngineTextureManager::GetInst().Find("LdoorAnimation.png");
		LdoorTexture->Cut(15, 1);

		GameEngineTexture* RdoorTexture = GameEngineTextureManager::GetInst().Find("RdoorAnimation.png");
		RdoorTexture->Cut(15, 1);

		GameEngineTexture* CCTVTexture = GameEngineTextureManager::GetInst().Find("CCTVAnimation.png");
		CCTVTexture->Cut(5, 2);

		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("WhiteNoise"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("ScanLine"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElec"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElecBlink"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElecFreddy"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareChica"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFoxy"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RunningFoxy"));
		GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFreddy"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("LdoorOpen"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorClose"));
		//	GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RdoorOpen"));

		imageDir.MoveChild("UI");

		std::vector<GameEngineFile> UI = imageDir.GetAllFile("png");

		for (size_t i = 0; i < UI.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(UI[i].GetFullPath());
		}

		imageDir.MoveParent("Play");
		imageDir.MoveChild("CCTV");
		imageDir.MoveChild("BackStage");

		std::vector<GameEngineFile> BackStage = imageDir.GetAllFile("png");

		for (size_t i = 0; i < BackStage.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(BackStage[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("DiningArea");

		std::vector<GameEngineFile> DiningArea = imageDir.GetAllFile("png");

		for (size_t i = 0; i < DiningArea.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(DiningArea[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("EastHallA");

		std::vector<GameEngineFile> EastHallA = imageDir.GetAllFile("png");

		for (size_t i = 0; i < EastHallA.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(EastHallA[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("EastHallB");

		std::vector<GameEngineFile> EastHallB = imageDir.GetAllFile("png");

		for (size_t i = 0; i < EastHallB.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(EastHallB[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("ETC");

		std::vector<GameEngineFile> ETC = imageDir.GetAllFile("png");

		for (size_t i = 0; i < ETC.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(ETC[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("ShowStage");

		std::vector<GameEngineFile> ShowStage = imageDir.GetAllFile("png");

		for (size_t i = 0; i < ShowStage.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(ShowStage[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("PirateCove");

		std::vector<GameEngineFile> PirateCove = imageDir.GetAllFile("png");

		for (size_t i = 0; i < PirateCove.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(PirateCove[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("RestRooms");

		std::vector<GameEngineFile> RestRooms = imageDir.GetAllFile("png");

		for (size_t i = 0; i < RestRooms.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(RestRooms[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("SupplyCloset");

		std::vector<GameEngineFile> SupplyCloset = imageDir.GetAllFile("png");

		for (size_t i = 0; i < SupplyCloset.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(SupplyCloset[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("WestHallA");

		std::vector<GameEngineFile> WestHallA = imageDir.GetAllFile("png");

		for (size_t i = 0; i < WestHallA.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(WestHallA[i].GetFullPath());
		}

		imageDir.MoveParent("CCTV");
		imageDir.MoveChild("WestHallB");

		std::vector<GameEngineFile> WestHallB = imageDir.GetAllFile("png");

		for (size_t i = 0; i < WestHallB.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(WestHallB[i].GetFullPath());
		}
	}
	

	// GameOver Level
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("GameOver");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}

	{
		//GameEngineDirectory soundDir;
		//soundDir.MoveParent("AR38Direct");
		//soundDir.MoveChild("Resources");
		//soundDir.MoveChild("Sound");
		//soundDir.MoveChild("GameOver");
	}

	// Custom Setting Level
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("CustomSetting");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}


	// Intermission Level
	{
		GameEngineDirectory imageDir;
		imageDir.MoveParent("AR38Direct");
		imageDir.MoveChild("Resources");
		imageDir.MoveChild("Image");
		imageDir.MoveChild("Intermission");

		std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");

		for (size_t i = 0; i < allFile.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
		}
	}

	AppShaderLoad();
}

void UserGame::ResourceCreate()
{
	// ���ǽ� �ݿ����� ������

	{
		std::vector<GameEngineVertex> HalfCylinderVertex = std::vector<GameEngineVertex>(4 * 8);

		{
			HalfCylinderVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[1] = { float4({ -0.75f, 1.0f, 0.05f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[2] = { float4({ -0.75f, -1.0f, 0.05f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[4] = { float4({ -0.75f, 1.0f, 0.05f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[5] = { float4({ -0.5f, 1.0f, 0.1f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[6] = { float4({ -0.5f, -1.0f, 0.1f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[7] = { float4({ -0.75f, -1.0f, 0.05f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[8] = { float4({ -0.5f, 1.0f, 0.1f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[9] = { float4({ -0.25f, 1.0f, 0.15f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[10] = { float4({ -0.25f, -1.0f, 0.15f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[11] = { float4({ -0.5f, -1.0f, 0.1f }),  { 0.0f, 1.0f } };

			// �߾�
			HalfCylinderVertex[12] = { float4({ -0.25f, 1.0f, 0.15f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[13] = { float4({ 0.0f, 1.0f, 0.15f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[14] = { float4({ 0.0f, -1.0f, 0.15f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[15] = { float4({ -0.25f, -1.0f, 0.15f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[16] = { float4({ 0.0f, 1.0f, 0.15f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[17] = { float4({ 0.25f, 1.0f, 0.15f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[18] = { float4({ 0.25f, -1.0f, 0.15f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[19] = { float4({ 0.0f, -1.0f, 0.15f }),  { 0.0f, 1.0f } };
			// �߾� ��

			HalfCylinderVertex[20] = { float4({ 0.25f, 1.0f, 0.15f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[21] = { float4({ 0.5f, 1.0f, 0.1f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[22] = { float4({ 0.5f, -1.0f, 0.1f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[23] = { float4({ 0.25f, -1.0f, 0.15f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[24] = { float4({ 0.5f, 1.0f, 0.1f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[25] = { float4({ 0.75f, 1.0f, 0.05f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[26] = { float4({ 0.75f, -1.0f, 0.05f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[27] = { float4({ 0.5f, -1.0f, 0.1f }),  { 0.0f, 1.0f } };

			HalfCylinderVertex[28] = { float4({ 0.75f, 1.0f, 0.05f }),  { 0.0f, 0.0f } };
			HalfCylinderVertex[29] = { float4({ 1.0f, 1.0f, 0.0f }),  { 1.0f, 0.0f } };
			HalfCylinderVertex[30] = { float4({ 1.0f, -1.0f, 0.0f }),  { 1.0f, 1.0f } };
			HalfCylinderVertex[31] = { float4({ 0.75f, -1.0f, 0.05f }),  { 0.0f, 1.0f } };
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
			});

		GameEngineIndexBufferManager::GetInst().Create("HalfCylinder", HalfCylinderIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


}