#pragma once
#include "GameEngineTransform.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 설명 : 순수히 디버그용 렌더링만 하기 위해서
//		  렌더링의 필수 요소인 트랜스폼, 쉐이더헬퍼, 렌파만 가져온 클래스입니다.


class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineDebugRenderData
{
	friend class CameraComponent;

public:
	// constrcuter destructer
	GameEngineDebugRenderData();
	~GameEngineDebugRenderData();

	// delete Function
	GameEngineDebugRenderData(const GameEngineDebugRenderData& _Other)
		: Data_(_Other.Data_)
		, ShaderHelper_(_Other.ShaderHelper_)
		, PipeLine_(_Other.PipeLine_)
	{

	}
	// GameEngineDebugRenderData(GameEngineDebugRenderData&& _Other) noexcept = delete;
	// GameEngineDebugRenderData& operator=(const GameEngineDebugRenderData& _Other) = delete;
	// GameEngineDebugRenderData& operator=(GameEngineDebugRenderData&& _Other) noexcept = delete;

protected:

private:
	TransformData Data_;
	float4 Color_;
	GameEngineShaderResHelper ShaderHelper_;
	GameEngineRenderingPipeLine* PipeLine_;

};

