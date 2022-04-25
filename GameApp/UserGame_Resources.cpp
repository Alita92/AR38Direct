#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine/EngineVertex.h>
#include "UserGame_Resources_Shader.h"


void TextureLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		// Sleep(10);
	}

	--UserGame::LoadingFolder;
}


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

	//GameEngineDirectory TextureDir;
	//TextureDir.MoveParent("AR38Direct");
	//TextureDir.MoveChild("Resources");
	//TextureDir.MoveChild("Image");
	//
	//std::vector<GameEngineDirectory> AllDir = TextureDir.GetAllDirectoryRecursive();
	//LoadingFolder = static_cast<int>(AllDir.size());
	//
	//for (size_t i = 0; i < AllDir.size(); i++)
	//{
	//	GameEngineCore::ThreadQueue.JobPost(std::bind(TextureLoading, AllDir[i]));
	//}


	GameEngineCore::ThreadQueue.JobPost(
		[]()
		{
			{
				//Title Level
				{
				GameEngineDirectory imageDir;
				imageDir.MoveParent("AR38Direct");
				imageDir.MoveChild("Resources");
				imageDir.MoveChild("Image");
				imageDir.MoveChild("Common");
				TextureLoading(imageDir);
				
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("WhiteNoise"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("ScanLine"));
					//std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
					//
					//for (size_t i = 0; i < allFile.size(); i++)
					//{
					//	GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
					//}
				}

				{
					GameEngineDirectory imageDir;
					imageDir.MoveParent("AR38Direct");
					imageDir.MoveChild("Resources");
					imageDir.MoveChild("Image");
					imageDir.MoveChild("Title");
					TextureLoading(imageDir);



					//	std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
					//
					//	for (size_t i = 0; i < allFile.size(); i++)
					//	{
					//		GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
					//	}
				}
			}

			// Play Level
			{
				GameEngineDirectory imageDir;
				imageDir.MoveParent("AR38Direct");
				imageDir.MoveChild("Resources");
				imageDir.MoveChild("Image");
				imageDir.MoveChild("Play");
				TextureLoading(imageDir);

				//	std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
				//
				//	for (size_t i = 0; i < allFile.size(); i++)
				//	{
				//		GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
				//	}

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


				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElec"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElecBlink"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("NoElecFreddy"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareChica"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFoxy"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("RunningFoxy"));
				GameEngineFolderTextureManager::GetInst().Load(imageDir.PathToPlusFileName("JumpScareFreddy"));

				imageDir.MoveChild("UI");
				TextureLoading(imageDir);

				//		std::vector<GameEngineFile> UI = imageDir.GetAllFile("png");
				//
				//		for (size_t i = 0; i < UI.size(); i++)
				//		{
				//			GameEngineTextureManager::GetInst().Load(UI[i].GetFullPath());
				//		}

				imageDir.MoveParent("Play");
				imageDir.MoveChild("Subtitles");
				imageDir.MoveChild("DAY1");
				TextureLoading(imageDir);

				//	std::vector<GameEngineFile> Day1Sub = imageDir.GetAllFile("png");
				//
				//	for (size_t i = 0; i < Day1Sub.size(); i++)
				//	{
				//		GameEngineTextureManager::GetInst().Load(Day1Sub[i].GetFullPath());
				//	}

				imageDir.MoveParent("Play");
				imageDir.MoveChild("Subtitles");
				imageDir.MoveChild("DAY2");
				TextureLoading(imageDir);

				imageDir.MoveParent("Play");
				imageDir.MoveChild("Subtitles");
				imageDir.MoveChild("DAY3");
				TextureLoading(imageDir);

				imageDir.MoveParent("Play");
				imageDir.MoveChild("Subtitles");
				imageDir.MoveChild("DAY4");
				TextureLoading(imageDir);


				imageDir.MoveParent("Play");
				imageDir.MoveChild("CCTV");
				imageDir.MoveChild("BackStage");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> BackStage = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < BackStage.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(BackStage[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("DiningArea");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> DiningArea = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < DiningArea.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(DiningArea[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("EastHallA");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> EastHallA = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < EastHallA.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(EastHallA[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("EastHallB");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> EastHallB = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < EastHallB.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(EastHallB[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("ETC");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> ETC = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < ETC.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(ETC[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("ShowStage");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> ShowStage = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < ShowStage.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(ShowStage[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("PirateCove");
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> PirateCove = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < PirateCove.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(PirateCove[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("RestRooms");

				TextureLoading(imageDir);
				//std::vector<GameEngineFile> RestRooms = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < RestRooms.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(RestRooms[i].GetFullPath());
				//}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("SupplyCloset");
				TextureLoading(imageDir);
				//		std::vector<GameEngineFile> SupplyCloset = imageDir.GetAllFile("png");
				//
				//		for (size_t i = 0; i < SupplyCloset.size(); i++)
				//		{
				//			GameEngineTextureManager::GetInst().Load(SupplyCloset[i].GetFullPath());
				//		}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("WestHallA");
				TextureLoading(imageDir);
				//	std::vector<GameEngineFile> WestHallA = imageDir.GetAllFile("png");
				//
				//	for (size_t i = 0; i < WestHallA.size(); i++)
				//	{
				//		GameEngineTextureManager::GetInst().Load(WestHallA[i].GetFullPath());
				//	}

				imageDir.MoveParent("CCTV");
				imageDir.MoveChild("WestHallB");
				TextureLoading(imageDir);
				//std::vector<GameEngineFile> WestHallB = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < WestHallB.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(WestHallB[i].GetFullPath());
				//}
			}


			// GameOver Level
			{
				GameEngineDirectory imageDir;
				imageDir.MoveParent("AR38Direct");
				imageDir.MoveChild("Resources");
				imageDir.MoveChild("Image");
				imageDir.MoveChild("GameOver");
				TextureLoading(imageDir);
				//std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < allFile.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
				//}
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
				TextureLoading(imageDir);

				//std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < allFile.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
				//}
			}


			// Intermission Level
			{
				GameEngineDirectory imageDir;
				imageDir.MoveParent("AR38Direct");
				imageDir.MoveChild("Resources");
				imageDir.MoveChild("Image");
				imageDir.MoveChild("Intermission");
				TextureLoading(imageDir);
				//std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < allFile.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
				//}
			}

			// Trial Over Level
			{
				GameEngineDirectory imageDir;
				imageDir.MoveParent("AR38Direct");
				imageDir.MoveChild("Resources");
				imageDir.MoveChild("Image");
				imageDir.MoveChild("TrialOver");
				TextureLoading(imageDir);
				//std::vector<GameEngineFile> allFile = imageDir.GetAllFile("png");
				//
				//for (size_t i = 0; i < allFile.size(); i++)
				//{
				//	GameEngineTextureManager::GetInst().Load(allFile[i].GetFullPath());
				//}
			}
		}
		);

	AppShaderLoad();
}
