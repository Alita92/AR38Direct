#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineReasterizerManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineReasterizer.h"
#include "GameEngineTexture.h"


class GameEngineManagerHeler
{
public:
	static void ManagerRealse()
	{
		GameEngineIndexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineReasterizerManager::Destroy();
		GameEngineTextureManager::Destroy();
		GameEngineSoundManager::Destroy();
	}
};
