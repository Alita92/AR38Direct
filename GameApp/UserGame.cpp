#include "PreCompile.h"
#include "UserGame.h"
#include <conio.h>

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
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
		// ���� ��ü�� ������ ũ��� ȸ������ ���� ����
		// ���ý����̽�

		// ���ü��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ�
		// ��ġ��Ű�� �ν��մϴ�.
		// ���彺���̽�

		std::vector<float4> RectVertex = std::vector<float4>(4 * 6);

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

	{
		std::vector<int> RectIndex;

		for (int i = 0; i < 6; i++)
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

		GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
			{
				// 1 0 0 0
				// 0 1 0 0
				// 0 0 1 0
				// 0 0 0 1

				float4x4 ScaleMat;
				ScaleMat.Scaling({ 1280.0f, 720.0f, 10.0f });

				float4x4 RotMat;
				RotMat.RotationDeg({ 0.0f, 0.0f, 0.0f });

				float4x4 PosMat;
				PosMat.Translation({ 0.0f, 0.0f, 0.0f });

				float4x4 ViewMat;
				ViewMat.ViewToLH({ 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f });

				// 

				// ������ ũ�⸦ -1 1������ ������ ���δ�.
				// X = -1~1;
				// Y = -1~1;
				// Z = 0~1;

				// ���� 2���� ��������� �ִµ�.
				// 1. ���ٰ��� �ִ� ������� ��������
				// 2. ���� �ʴ� ������� ��������

				// -1~1�� ���� �������� �ٲߴϴ�.


				float4x4 PerspectiveMat;
				PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);


				float4x4 OrthographicMat;
				OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);

				// ProjectionMat.P




			// ���Ͷ�?
			// ������������ �����ϴ� x y
			// 2 2
			// 50 40
			// 2, 2


			// 51 41
			// 52, 42


			// ����� ��ȯ��Ģ�� �������� �ʽ��ϴ�.
			// ũ���̰���
			// ũ��
			// ����
			// �̵�
			// ����
			// �θ�

				float4x4 WorldMat = ScaleMat * RotMat * PosMat;

				float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat;

				float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat;


				float4 PersPos = _Value;
				PersPos *= WorldViewProjectionMat;

				float4 OrthPos = _Value;
				OrthPos *= WorldViewOrthographicMat;


				int a = 0;

				return PersPos;
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
	BoxPos.y += 10.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();

}

