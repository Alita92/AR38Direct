#include "PreCompile.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include "Player.h"
#include "Bullet.h"

Player::Player()
{
}

Player::~Player()
{
}



void Player::Start()
{
	// 정말 세팅해줘야할게 많은 녀석입니다.
	// 랜더러로서 뭐든지 다 그릴수있는 가능성을 가지고 있는 녀석.
	{
		PlayerImageRenderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		PlayerImageRenderer->SetImage("Char.png", true);
		//PlayerImageRenderer->GetTransform()->SetLocalScaling({ 100.0f, 100.0f, 1.0f });
	}

	{	
		//GameEngineRenderer* Renderer = CreateTransformComponent<GameEngineRenderer>(GetTransform());
		//Renderer->SetRenderingPipeLine("Color");
		//Renderer->GetTransform()->SetLocalScaling({ 100.0f, 20.0f, 1.0f });
		//Renderer->GetTransform()->SetLocalPosition({ 0.0f, 80.0f, 0.0f });
		//Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));
	}

	if (false == GameEngineInput::GetInst().IsKey("PlayerMove"))
	{
		GameEngineInput::GetInst().CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst().CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst().CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst().CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst().CreateKey("RotZ+", 'Q');
		GameEngineInput::GetInst().CreateKey("RotZ-", 'E');
		GameEngineInput::GetInst().CreateKey("Fire", VK_SPACE);
	}
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst().Press("MoveLeft"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::LEFT * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveRight"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::RIGHT * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveUp"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::UP * 100.0f);
	}
	if (true == GameEngineInput::GetInst().Press("MoveDown"))
	{
		GetTransform()->SetLocalDeltaTimeMove(float4::DOWN * 100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ+"))
	{
		// 렌더러의 트랜스폼만 건드려서 자식 액터(체력바 등의 개인 UI) 는 회전하지 않도록 한다.
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, 1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Press("RotZ-"))
	{
		PlayerImageRenderer->GetTransform()->SetLocalDeltaTimeRotation(float4{ 0.0f, 0.0f, -1.0f } *100.0f);
	}

	if (true == GameEngineInput::GetInst().Down("Fire"))
	{
		Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
		NewBullet->GetTransform()->SetLocalPosition(this->GetTransform()->GetLocalPosition());
		NewBullet->Release(1.0f);
	}

	// 카메라 포커싱을 담당하는 코드
	// 메인 카메라에 직접 접근해 포지션을 this 에 맞춘다.
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(this->GetTransform()->GetLocalPosition());

}