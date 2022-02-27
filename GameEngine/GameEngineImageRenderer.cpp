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
}

void GameEngineImageRenderer::SetImage(const std::string& _ImageName, bool _originalScale)
{
	if (true == _originalScale)
	{
		ShaderHelper.SettingTexture("Tex", _ImageName);

		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
			
		this->GetTransform()->SetLocalScaling({static_cast<float>(FindTexture->GetTextureResolutionX()), static_cast<float>(FindTexture->GetTextureResolutionY()), 1.0f});

		return;
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);
}