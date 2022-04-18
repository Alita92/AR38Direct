#include "PreCompile.h"
#include "GameEnginePostProcessRender.h"
#include <GameEngine\GameEngineWindow.h>

GameEnginePostProcessRender::GameEnginePostProcessRender()
	: Target_(nullptr)
	, Effect_(nullptr)
	, IsResultCreate_(false)
	, Result_(nullptr)
	, prevTarget_(nullptr)
{
}

GameEnginePostProcessRender::~GameEnginePostProcessRender()
{
	if (true == IsResultCreate_)
	{
		delete Result_;
		Result_ = nullptr;
	}

	if (nullptr != prevTarget_)
	{
		delete prevTarget_;
		prevTarget_ = nullptr;
	}
}

void GameEnginePostProcessRender::CreateResultTarget()
{
	Result_ = new GameEngineRenderTarget();
	Result_->Create(GameEngineWindow::GetInst().GetSize(), float4::NONE);
	Result_->CreateDepthBuffer(GameEngineWindow::GetInst().GetSize());
	IsResultCreate_ = true;
}

void GameEnginePostProcessRender::CreatePrevTarget()
{
	prevTarget_ = new GameEngineRenderTarget();
	prevTarget_->Create(GameEngineWindow::GetInst().GetSize(), float4::NONE);
	prevTarget_->CreateDepthBuffer(GameEngineWindow::GetInst().GetSize());
}


void GameEnginePostProcessRender::Initialize()
{

}


