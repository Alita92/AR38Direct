#include "PreCompile.h"
#include "GameOverLevel.h"

// Actor
#include "GameOverBackground.h"

GameOverLevel::GameOverLevel() // default constructer ����Ʈ ������
{

}

GameOverLevel::~GameOverLevel() // default destructer ����Ʈ �Ҹ���
{

}

GameOverLevel::GameOverLevel(GameOverLevel&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}


void GameOverLevel::LevelStart()
{

	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	{
		// ���ӿ��� ���ȭ��� �ؽ�Ʈ �����Դϴ�.
		GameOverBackground* gameOverBackground = CreateActor<GameOverBackground>();
	}
}
void GameOverLevel::LevelUpdate(float _DeltaTime)
{

}
void GameOverLevel::LevelChangeEndEvent()
{

}
void GameOverLevel::LevelChangeStartEvent()
{

}