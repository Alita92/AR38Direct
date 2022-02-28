#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTransformComponent.h"
#include "GameEngineTransform.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include "GameEngineTextureManager.h"
GameEngineImageRenderer::GameEngineImageRenderer()
{
}

GameEngineImageRenderer::~GameEngineImageRenderer()
{
}

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
	// 이미지 스프라이트 렌더링은 무조건 Texture 로 하기로
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, bool _originalScale)
{
	if (true == _originalScale)
	{
		ShaderHelper.SettingTexture("Tex", _ImageName); // 사실상의 텍스처가 세팅되는 순간

		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
			
		this->GetTransform()->SetLocalScaling({static_cast<float>(FindTexture->GetTextureResolutionX()), static_cast<float>(FindTexture->GetTextureResolutionY()), 1.0f});

		return;
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);
}