#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineDepthBuffer.h"

GameEngineRenderTarget::GameEngineRenderTarget() // default constructer 디폴트 생성자
	: DepthBuffer_(nullptr)
{
	Pipe_ = GameEngineRenderingPipeLineManager::GetInst().Find("TargetMerge");
	Res_.ShaderResourcesCheck(Pipe_);
}

GameEngineRenderTarget::~GameEngineRenderTarget() // default destructer 디폴트 소멸자
{
	for (size_t i = 0; i < ReleaseTextures_.size(); i++)
	{
		delete ReleaseTextures_[i];
	}

	if (nullptr != DepthBuffer_)
	{
		delete DepthBuffer_;
	}
}

GameEngineRenderTarget::GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

void GameEngineRenderTarget::Clear(bool _Death /*= true*/)
{
	for (size_t i = 0; i < RenderTargetViews_.size(); i++)
	{
		GameEngineDevice::GetContext()->ClearRenderTargetView(RenderTargetViews_[i], ClearColor_[i].Arr1D);
	}

	if (nullptr != DepthBuffer_ && true == _Death)
	{
		GameEngineDevice::GetContext()->ClearDepthStencilView(DepthBuffer_->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}


void GameEngineRenderTarget::Create(const std::string _TextureName, float4 _ClearColor)
{
	GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_TextureName);
	if (nullptr == FindTexture)
	{
		GameEngineDebug::MsgBoxError("FindTexture Is null Create Render Target Error");
	}

	FindTexture->CreateRenderTargetView();
	FindTexture->CreateShaderResourceView();

	Create(FindTexture, _ClearColor);
}

void GameEngineRenderTarget::Create(float4 _Size, float4 _ClearColor)
{
	GameEngineTexture* NewTexture = new GameEngineTexture();

	NewTexture->Create(_Size, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

	ReleaseTextures_.push_back(NewTexture);

	Create(NewTexture, _ClearColor);
}

void GameEngineRenderTarget::CreateDepthBuffer(float4 _Scale)
{
	if (nullptr != DepthBuffer_)
	{
		return;
	}

	DepthBuffer_ = new GameEngineDepthBuffer();
	DepthBuffer_->Create(_Scale);
}


void GameEngineRenderTarget::Create(GameEngineTexture* _Texture, float4 _ClearColor)
{
	Textures_.push_back(_Texture);
	RenderTargetViews_.push_back(_Texture->GetRenderTargetView());
	ShaderResourcesViews_.push_back(*_Texture->GetShaderResourcesView());
	ClearColor_.push_back(_ClearColor);
}


void GameEngineRenderTarget::Setting(int _Index)
{

	// 해당 렌더타겟을 나올 수 있게 세팅하는 함수

	if (0 >= RenderTargetViews_.size())
	{
		GameEngineDebug::MsgBoxError("Render Target Setting Error Size Zero");
	}

	ID3D11DepthStencilView* View = nullptr;

	if (nullptr != DepthBuffer_)
	{
		View = DepthBuffer_->GetDepthStencilView();
	}


	if (-1 == _Index)
	{
		GameEngineDevice::GetContext()->OMSetRenderTargets(static_cast<UINT>(RenderTargetViews_.size()), &RenderTargetViews_[0], nullptr);
		// 아웃풋 머져에 갈 렌더타겟 뷰를 설정한다.
	}
	else
	{
		GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RenderTargetViews_[_Index], nullptr);
	}
}


void GameEngineRenderTarget::Merge(GameEngineRenderTarget* _Other, int _Index)
{
	// 먼저 "현재" 설정된 렌더타겟을 세팅한다.
	Setting();

	// 이제 세팅된 렌더타겟 위에 덧그린다...

	Res_.SettingTexture("Tex", _Other->Textures_[_Index]);
	// 현 2D 포폴에선 어차피 셰이더는 Texture 만 사용하니...
	// Texture 셰이더의 텍스처2D 인 Tex 로 고정하자.
	
	Res_.Setting();
	// 설정한 셰이더 리소스를 세팅해주고...

	Pipe_->Rendering();
	// 기설정된 렌더링 파이프라인을 세팅하고
	// DrawIndexed 함수를 사용해 인덱스대로 버텍스들을 그린다.

	Pipe_->Reset();
	// 블렌드와 깊이 스텐실 리셋
	Res_.ReSet();
	// 리소스들의 값들을 모두 지워 준다
}



void GameEngineRenderTarget::Copy(GameEngineRenderTarget* _Other)
{
	Clear();
	Merge(_Other);
}