#include "PreCompile.h"
#include "GameEngineBackgroundRenderer.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTransform.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

void GameEngineBackgroundRenderer::Animation2D::CallStart()
{
	for (auto& CallBack : StartCallBack_)
	{
		CallBack();
	}
}
void GameEngineBackgroundRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}
void GameEngineBackgroundRenderer::Animation2D::CallFrame()
{
	for (auto& CallBack : FrameCallBack_)
	{
		if (CallBack.first != CurFrame_) // 콜백의 키값(프레임) 이 현 프레임이 아니면...
		{// 패스
			continue;
		}

		if (CallBack.second.size() == 0) // 콜백이 없어도..
		{ // 패스
			continue;
		}

		for (size_t i = 0; i < CallBack.second.size(); i++)
		{ // 그 이외의 상황(키값이 현 프레임이고, 콜백이 있다면)
			// 실행
			CallBack.second[i]();
		}
	}
}

void GameEngineBackgroundRenderer::Animation2D::Reset()
{
	IsEnd = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineBackgroundRenderer::Animation2D::FrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		++CurFrame_;
		CurTime_ = InterTime_;
		if (true == Loop_
			&& CurFrame_ > EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_
			&& CurFrame_ > EndFrame_)
		{
			if (false == IsEnd)
			{
				CallEnd();
			}

			IsEnd = true;

			CurFrame_ = EndFrame_;
		}
	}

}

void GameEngineBackgroundRenderer::Animation2D::ReverseFrameUpdate()
{
	if (CurTime_ <= 0.0f)
	{
		--CurFrame_;
		CurTime_ = InterTime_;
		if (true == Loop_
			&& CurFrame_ < EndFrame_)
		{
			CallEnd();
			CurFrame_ = StartFrame_;
		}
		else if (false == Loop_
			&& CurFrame_ < EndFrame_)
		{
			if (false == IsEnd)
			{
				CallEnd();
			}

			IsEnd = true;

			//CurFrame_ = StartFrame_;
			CurFrame_ = EndFrame_;
		}
	}

}

void GameEngineBackgroundRenderer::Animation2D::Update(float _DeltaTime)
{
	CurTime_ -= _DeltaTime;

	if (StartFrame_ < EndFrame_)
	{
		FrameUpdate();
	}
	else
	{
		ReverseFrameUpdate();
	}

	CallFrame();
	if (nullptr == FolderTextures_)
	{
		Renderer->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
		Renderer->CurTexture = AnimationTexture_;
		Renderer->SetIndex(CurFrame_);
	}
	else
	{
		Renderer->CutData = float4(0, 0, 1, 1);
		Renderer->ShaderHelper.SettingTexture("Tex", FolderTextures_->GetTextureIndex(CurFrame_));
	}

}

/// ///////////////////////////////////////////////////////////////////

GameEngineBackgroundRenderer::GameEngineBackgroundRenderer()
	: CutData(0, 0, 1, 1)
	, CurAnimation_(nullptr)
	//, isAnimationImageSwapped_(false)
{
}

GameEngineBackgroundRenderer::~GameEngineBackgroundRenderer()
{
	for (auto& Animation : AllAnimations_)
	{
		if (nullptr == Animation.second)
		{
			continue;
		}

		delete Animation.second;
		Animation.second = nullptr;
	}
}

void GameEngineBackgroundRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("TextureBackground");

	ImageRendererStart();
}

void GameEngineBackgroundRenderer::ImageRendererStart()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData);

	ResultColor = float4::ONE;
	ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor);
}

void GameEngineBackgroundRenderer::SetIndex(const int Index)
{
	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("텍스처가 존재하지 않는데 인덱스를 지정하려고 했습니다");
	}

	if (false == CurTexture->IsCut())
	{
		GameEngineDebug::MsgBoxError("잘리지 않은 텍스처의 인덱스를 지정하려고 했습니다.");
	}

	CutData = CurTexture->GetCutData(Index);

}


void GameEngineBackgroundRenderer::SetImage(const std::string& _ImageName, bool _originalScale)
{
	//isAnimationImageSwapped_ = true;
	CurTexture = GameEngineTextureManager::GetInst().Find(_ImageName);

	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처를 세팅하려고 했습니다");
		return;
	}

	if (true == _originalScale)
	{
		ShaderHelper.SettingTexture("Tex", _ImageName); // 사실상의 텍스처가 세팅되는 순간

		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
		GetTransform()->SetLocalScaling({ FindTexture->GetTextureSize().x, FindTexture->GetTextureSize().y, 1.0f });
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);
}

void GameEngineBackgroundRenderer::CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop /*= true*/)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->AnimationTexture_ = GameEngineTextureManager::GetInst().Find(_TextureName);

	if (nullptr == NewAnimation->AnimationTexture_)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처로 애니메이션을 만들려고 했습니다.");
	}


	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = nullptr;
	NewAnimation->CurFrame_ = _StartFrame;
	NewAnimation->EndFrame_ = _EndFrame;
	NewAnimation->StartFrame_ = _StartFrame;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineBackgroundRenderer::CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop /*= true*/)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() != FindIter)
	{
		GameEngineDebug::MsgBoxError("이미 존재하는 애니메이션을 또 만들었습니다.");
	}

	GameEngineFolderTexture* FolderTexture = GameEngineFolderTextureManager::GetInst().Find(_FolderTexName);

	if (nullptr == FolderTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 폴더 텍스처를 세팅하려고 했습니다..");
	}


	Animation2D* NewAnimation = new Animation2D();

	NewAnimation->SetName(_Name);
	NewAnimation->IsEnd = false;
	NewAnimation->Loop_ = _Loop;
	NewAnimation->InterTime_ = _InterTime;
	NewAnimation->CurTime_ = _InterTime;

	NewAnimation->FolderTextures_ = FolderTexture;
	NewAnimation->CurFrame_ = 0;
	NewAnimation->EndFrame_ = FolderTexture->GetTextureCount() - 1;
	NewAnimation->StartFrame_ = 0;
	NewAnimation->Renderer = this;

	AllAnimations_.insert(std::map<std::string, Animation2D*>::value_type(_Name, NewAnimation));
}

void GameEngineBackgroundRenderer::SetChangeAnimation(const std::string& _Name, bool _IsForce /*= false*/)
{
	//isAnimationImageSwapped_ = false;
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	if (false == _IsForce && CurAnimation_ == FindIter->second)
	{
		return;
	}

	CurAnimation_ = FindIter->second;
	if (nullptr == CurAnimation_->FolderTextures_)
	{
		ShaderHelper.SettingTexture("Tex", CurAnimation_->AnimationTexture_);
	}
	CurAnimation_->Reset();
	CurAnimation_->CallStart();
}

void GameEngineBackgroundRenderer::Update(float _DeltaTime)
{
	if (nullptr == CurAnimation_)
	{
		return;
	}

	//if (false == isAnimationImageSwapped_)
	{
		CurAnimation_->Update(_DeltaTime);
	}

}

void GameEngineBackgroundRenderer::SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->StartCallBack_.push_back(_CallBack);
}
void GameEngineBackgroundRenderer::SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->EndCallBack_.push_back(_CallBack);
}
void GameEngineBackgroundRenderer::SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack)
{
	std::map<std::string, Animation2D*>::iterator FindIter = AllAnimations_.find(_Name);

	if (AllAnimations_.end() == FindIter)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 애니메이션을 세팅하려고 했습니다");
	}

	if (nullptr == FindIter->second)
	{
		GameEngineDebug::MsgBoxError("애니메이션의 애니메이션 nullptr 입니다");
	}

	FindIter->second->FrameCallBack_[_Index].push_back(_CallBack);
}