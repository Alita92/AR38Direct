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

void UserGame::ResourcesLoad()
{
	{
		GameEngineDirectory SoundDir;
		SoundDir.MoveParent("AR38");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}


	{
		// 버텍스 버퍼 : 정점의 정보를 저장해준다.
		std::vector<float4> RectVertex = std::vector<float4>(4);

		RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
		RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
		RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
		RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

		//RectVertex[4] = RectVertex[0].Rotatefloat2Degree();
		//RectVertex[5] = RectVertex[1]
		//RectVertex[6] = RectVertex[2]
		//RectVertex[7] = RectVertex[3]

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);
	}

	{
		// 인덱스 버퍼 : 정점을 나열하는 순서를 저장해준다.
		std::vector<int> RectIndex = { 0,1,2, 0,2,3 };
		// 현 프레임워크에서 프리미티브는 삼각형, 따라서 버텍스는 3개씩 묶여야 한다.
		// 프리미티브 : 렌더링을 할 수 있는 최소한의 도형
		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);
	}

	{
		// 버텍스 쉐이더 : 정점 정보에 수학적인 연산을 해 특정 행동을 실행한다.

		// [](인자){코드}
		// "람다 식". 즉석에서 함수를 하나 만들어 내 사용할 수 있다.

		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				float4 MovePos = { 200.0f, 200.0f };
				float4 Pos = _Value;
				Pos *= 100.0f;
				Pos.Rotatefloat2Degree(RotAngle);
				Pos += MovePos;

				return Pos;
			}
		);
	}

}

void UserGame::Release()
{

	// Resources
	GameEngineIndexBufferManager::Destroy();
	GameEngineVertexShaderManager::Destroy();
	GameEngineVertexBufferManager::Destroy();
	GameEngineTextureManager::Destroy();
	GameEngineSoundManager::Destroy();

	// Base
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}

void UserGame::GameLoop()
{

	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();

	// Polygon(GameEngineWindow::GetInst().GetWindowDC(), PolyGon, 4);

	// 지역 static
	//static float X = 0.0f;
	//X += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Rectangle(GameEngineWindow::GetInst().GetWindowDC(), 0 + X, 0, 100 + X, 100);
}