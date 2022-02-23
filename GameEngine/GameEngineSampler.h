#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineSampler : public GameEngineObjectNameBase
{
public:
	friend class GameEngineSamplerManager;

	void ReSetting(const D3D11_SAMPLER_DESC& _Info); // 다른 샘플링 필터를 쓰고 싶을때

	GameEngineSampler(); // default constructer 디폴트 생성자
	~GameEngineSampler(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineSampler(const GameEngineSampler& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:		//delete operator
	ID3D11SamplerState* State_; // 현재 샘플러 상태
	D3D11_SAMPLER_DESC Info_; // 샘플러 설정값

	void Create(const D3D11_SAMPLER_DESC& _Info); // 샘플러 생성
};

