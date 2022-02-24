#pragma once
#include "GameEngineRenderer.h"

// 설명 : 렌더러 중 이미지 파일을 렌더링하기 용이하게 만든 서브렌더러
//		  Start() 내부에서 렌더링 파이프라인을 돌리며, 
//		  기설정된 텍스처를 세팅해줍니다.

class GameEngineImageRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	// delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer(GameEngineImageRenderer&& _Other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer& operator=(GameEngineImageRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _ImageName);


protected:

private:
	void Start() override;

};

