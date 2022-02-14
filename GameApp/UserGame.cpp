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

struct TransformData
{
	float4x4 Scale;
	float4x4 Rotation;
	float4x4 Position;
	float4x4 World;
	float4x4 View;
	float4x4 Proj;

public:
	void CalWorld()
	{
		World = Scale * Rotation * Position;
	}
};


float4 Pos;
TransformData TransData; // 상수 버퍼(예시)


void UserGame::Initialize()
{
	TransData.View.ViewToLH({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f , 1.0f }, { 0.0f, 1.0f , 0.0f });

	TransData.Proj.OrthographicLH(1280.f, 720.f, 0.1f, 1000.0f);


	TransData.Scale.Scaling2D(200.0f);
	TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	TransData.CalWorld();


	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	// cpu의 데이터와 상수버퍼를 연결한다.

	Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);


	// Pipe->ShaderHelper.SettingConstantBufferLink("TransformData222", TransData);
	// cpu의 데이터와 상수버퍼를 한번 복사한다.
	// Pipe->ShaderHelper.SettingConstantBufferSet("TransformData", TransData);

	return;
}

void UserGame::Release()
{

}

float4 vPos = { 0.0f, 0.0f , 0.0f };
float4 vRot = { 0.0f, 0.0f , 0.0f };
float4 vScale = { 1.0f, 1.0f , 1.0f };

//void UserGame::GameLoop()
//{
//	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
//	{
//		Pos.x += 0.001f;
//		TransData.World.Translation(Pos);
//
//
//		//		만약 Initialize() 에서 파이프라인의 상수 버퍼 세팅을 "Set" 으로 했다면?
//		//		Pipe->ShaderHelper.SettingConstantBufferSet("TransformData", TransData);
//		//		루프마다 이걸 계속 프레임마다 실행해서 초기화를 해 주어야 한다
//		//		왜냐? 상수 버퍼값이 Set은 처음 설정한 값으로 고정이 되어버렸기 때문에... 변형된 TransData 로 계속 초기화를 해 주어야 한다.
//		//		Link 는 그냥 포인터로 연동이 되어 있어서 실시간으로 업데이트가 가능하다...
//
//
//		// 랜더링 파이프라인이 하나가 돌고
//		// 이안에 세팅정보가 존재하겠죠?
//		GameEngineDevice::RenderStart();
//
//		// 매프레임마다 세팅해줘야 하는게 되죠?
//		// 
//		Pipe->Rendering();
//		GameEngineDevice::RenderEnd();
//	}
//}

