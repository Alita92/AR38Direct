#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}



void UserGame::Initialize()
{

	GameEngineSoundManager::GetInst().Initialize();
	return;
}

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };

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

		std::vector<float4> RectVertex = std::vector<float4>(4 * 6);
		// "Rect" 도형 버텍스의 정보 리소스 묶음입니다.
		{
			RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
			RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
			RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
			RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

			RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
			RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
			RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
			RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);
		}

		{
			RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
			RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
			RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
			RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

			RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
			RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
			RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
			RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);
		}

		{
			RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
			RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
			RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
			RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

			RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
			RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
			RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
			RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);
		}

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}

	{ // 인덱스 버퍼 정보 : 정점의 순번과 프리미티브 형태의 리소스
		std::vector<int> RectIndex;

		for (int i = 0; i < 6; i++) // 3개씩 나눠서 푸시백 하는 이유? 현재 프리미티브는 삼각형이며, 삼각형 두 개를 합쳐서(= 정점 3개와 3개 묶음을 합쳐서) 1개의 사각 면을 구성한다. 
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
	}

	{
		// Vertex Shader 정보 : 버텍스 버퍼에 들어온 정점 정보들을 리소스의 의도대로 사이즈조절, 회전, 이동시킨다.
		// [혼합]
		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				// 모든 셰이딩 과정은
				// 크기 -> 자전 -> 이동 -> 공전 -> 부모
				//		-> 뷰   -> 투영
				// 순으로 곱연산되어 사용되어야 한다.

				float4x4 ScaleMat;
				ScaleMat.Scaling({ 20.0f, 20.0f, 20.0f }); // Scaling : 크기 조절

				float4x4 RotMat;
				RotMat.RotationDeg({ 0.0f, 0.0f, 0.0F }); // Rotation : 자전 조절
				// RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });

				float4x4 PosMat;
				// PosMat.Translation({ 0.0f, 0.0f, 0.0f });
				PosMat.Translation(BoxPos); // Translation : 이동 조절

				float4x4 ViewMat;
				ViewMat.ViewToLH({ 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }); // 좌수 좌표계에 의한 뷰 행렬 생성

				float4x4 PerspectiveMat;
				PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f); // 원근투영에 의한 곱연산

				float4x4 OrthographicMat;
				OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f); // 직교투영에 의한 곱연산

				// 세계의 크기를 -1 1사이의 값으로 줄인다.
				// X = -1~1;
				// Y = -1~1;
				// Z = 0~1;

				// 보통 2가지 투영행렬이 있는데.
				// 1. 원근감을 주는 투영행렬 원근투영
				// 2. 주지 않는 투영행렬 직교투영

				// -1~1로 들어가기 직전으로 바꿉니다.

				// ProjectionMat.P

				// 벡터란?
				// 원점에서부터 시작하는 x y
				// 2 2
				// 50 40
				// 2, 2

				{	// 테스트 벡터를 생성해 값을 확인해봅니다.
					// float4 VectorTest = { 0.0f, 0.0f, 100.0f, 2.0f };
					float4 VectorTest = { 0.0f, 0.0f, 100.0f, 1.0f };

					float4x4 TestMat;

					TestMat.vx = { 0.1f, 0.0f , 0.0f , 0.0f };
					TestMat.vy = { 0.0f, 0.1f , 0.0f , 0.0f };
					TestMat.vz = { 0.0f, 0.0f , 0.1f , 1.0f };
					TestMat.vw = { 0.0f, 0.0f , 0.0f , 0.0f };

					// 이 방식으로 월드 뷰까지 곱해졌을때의 z를 이미 w에 보관한겁니다.
					VectorTest *= TestMat;
				}

				float4x4 WorldMat = ScaleMat * RotMat * PosMat; // 크기 * 회전 * 이동
				float4x4 WorldView = WorldMat * ViewMat; // 뷰행렬

				float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat; // * 원근투영
				
				float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat; // * 직교투영

				float4 PersPos = _Value;
				PersPos *= WorldViewProjectionMat; // 원근투영 시점을 볼려면 PersPos 리턴하기

				float4 OrthPos = _Value;
				OrthPos *= WorldViewOrthographicMat; // 직교투영 시점을 볼려면 OrthPos 리턴하기

				//PersPos.x = PersPos.x / PersPos.w;
				//PersPos.y = PersPos.y / PersPos.w;
				//PersPos.z = PersPos.z / PersPos.w;
				//PersPos.w = 1.0f;

				return PersPos;
			}
		);
	}

	{

		GameEngineReasterizer* Ptr = GameEngineReasterizerManager::GetInst().Create("TestReasterizer");

		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	}

}

void UserGame::Release()
{

	// Resources
	GameEngineManagerHeler::ManagerRealse();
	// Base
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}

void UserGame::GameLoop()
{

	GameEngineRenderingPipeLine Pipe; // 현 구조에서는 한 렌더링에 한 파이프라인이 만들어져야 한다.
	// 렌더링을 위한 ResourceLoad() 는 Start() 단계에서 실행되어있다.
	
	// 하기 함수들에 24일(월) Directx 함수를 채워 줄 예정이다.
	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");
	Pipe.SetRasterizer("TestReasterizer");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();
	BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();

}

