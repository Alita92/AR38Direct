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

	return;
}

float RotAngle = 0.0f;
float4 BoxPos = { 0.0f, 0.0f, 0.0f };


void UserGame::Release()
{

}

void UserGame::GameLoop()
{
	GameEngineDirectXDevice::RenderStart();

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");
	Pipe->Rendering();

	// 메테리얼

	//GameEngineRenderingPipeLine Pipe;

	//// 매쉬
	//Pipe.SetInputAssembler1("Rect"); // 버텍스 버퍼
	//Pipe.SetInputAssembler2("Rect"); // 인덱스 버퍼

	//// 메테리얼
	//Pipe.SetVertexShader("TestShader"); // 어떻게 움직일래??????
	//Pipe.SetRasterizer("TestReasterizer");
	//RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();
	//BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();
	//Pipe.Rendering();


	GameEngineDirectXDevice::RenderEnd();
}
