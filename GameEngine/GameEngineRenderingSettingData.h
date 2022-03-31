#pragma once
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineSampler.h"
#include "GameEngineTexture.h"


enum class SettingMode
{
	Link,
	Set,
	MAX,
};

// 셰이더 리소스인 상수 버퍼, 샘플러, 텍스처의 세팅을 관리

class GameEngineShader;
class GameEngineConstantBuffer;
class GameEngineConstantBufferSetting // 상수 버퍼의 옵션창 역할
{
public:
	GameEngineShader* Shader;
	GameEngineConstantBuffer* Res_;
	SettingMode Mode_;
	char* SettingData_;
	size_t SettingDataSize_;
	int SettingIndex_;

public:
	void Clear()
	{
		if (SettingMode::Set == Mode_)
		{
			if (nullptr != SettingData_)
			{
				delete SettingData_;
				SettingData_ = nullptr;
			}
		}
	}

	void ChangeData()
	{
		Res_->ChangeData(SettingData_, SettingDataSize_);
	}

	void ShaderSetting()
	{
		Shader->SetConstantBuffers(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetConstantBuffers(this);
	}


public:
	GameEngineConstantBufferSetting()
		: SettingData_(nullptr)
		, Mode_(SettingMode::MAX)
		, Shader(nullptr)
		, Res_(nullptr)
		, SettingDataSize_(0)
		, SettingIndex_(0)
	{

	}

	~GameEngineConstantBufferSetting()
	{
		Clear();
	}
};


class GameEngineShader;
class GameEngineSampler;
class GameEngineSamplerSetting
{
public:
	GameEngineShader* Shader;
	GameEngineSampler* Res_;
	int SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader->SetSampler(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetSampler(this);
	}

public:
	GameEngineSamplerSetting()
		: Res_(nullptr), Shader(nullptr), SettingIndex_(0)
	{

	}

	~GameEngineSamplerSetting()
	{
	}
};

class GameEngineShader;
class GameEngineTexture;
class GameEngineTextureSetting
{
public:
	GameEngineShader* Shader;
	GameEngineTexture* Res_;
	int SettingIndex_;

public:
	void ShaderSetting()
	{
		Shader->SetTexture(this);
	}

	void ShaderReSet()
	{
		Shader->ReSetTexture(this);
	}

public:
	GameEngineTextureSetting()
		: Res_(nullptr), Shader(nullptr), SettingIndex_(0)
	{

	}

	~GameEngineTextureSetting()
	{
	}
};