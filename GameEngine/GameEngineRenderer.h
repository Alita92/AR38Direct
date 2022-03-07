#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 설명 : 하나의 랜더 단위를 표현합니다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
private:
	friend GameEngineLevel;
	friend CameraComponent;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetRenderingPipeLine(const std::string& _Value);
	virtual void SetRenderGroup(int _Order); // protected 가 이미지 렌더러에 상속되지가 않아서 임시로 일단 여기 배치
	GameEngineShaderResHelper ShaderHelper;

protected:
	GameEngineRenderingPipeLine* PipeLine_;

	void Start() override;

	// virtual void SetRenderGroup(int _Order);

private:
	void Update(float _DeltaTime) override;

	virtual void Render();

};

