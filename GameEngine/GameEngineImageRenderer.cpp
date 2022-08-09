#include "PreCompile.h"
#include "GameEngineImageRenderer.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTransform.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

void GameEngineImageRenderer::Animation2D::CallStart()
{
	for (auto& CallBack : StartCallBack_)
	{
		CallBack();
	}
}
void GameEngineImageRenderer::Animation2D::CallEnd()
{
	for (auto& CallBack : EndCallBack_)
	{
		CallBack();
	}
}
void GameEngineImageRenderer::Animation2D::CallFrame()
{
	// 특정 프레임에 실행시켜 줄 함수가 있다면...

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

void GameEngineImageRenderer::Animation2D::Reset()
{
	IsEnd = false;
	CurTime_ = InterTime_;
	CurFrame_ = StartFrame_;
}

void GameEngineImageRenderer::Animation2D::FrameUpdate()
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

void GameEngineImageRenderer::Animation2D::ReverseFrameUpdate()
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

void GameEngineImageRenderer::Animation2D::Update(float _DeltaTime)
{
	// 렌더러 역시 트랜스폼 컴포넌트이기 때문에 액터가 업데이트 되면서 같이 업데이트됩니다.

	CurTime_ -= _DeltaTime;
	// 델타타임 차감

	if (StartFrame_ < EndFrame_) // 시작 프레임보다 끝 프레임이 작다면... 프레임을 델타타임에 맞게 업데이트
	{
		FrameUpdate();
	}
	else
	{
		// 끝 프레임이 시작보다 작다면, 반대로 프레임을 업데이트
		ReverseFrameUpdate();
	}

	CallFrame(); // 특정 프레임에 실행시켜 줄 함수가 있다면...

	if (nullptr == FolderTextures_) // 폴더텍스처가 아니라면...
	{	// Texture2D 버퍼인 Tex 에 해당 텍스처 바로 세팅
		Renderer->ShaderHelper.SettingTexture("Tex", AnimationTexture_);
		Renderer->CurTexture = AnimationTexture_;
		Renderer->SetIndex(CurFrame_);
		// 인덱스를 프레임에 맞게 바꿔서 잘린 텍스처 중 순서에 맞는 걸 게시한다
	}
	else
	{
		Renderer->CutData = float4(0, 0, 1, 1);
		Renderer->ShaderHelper.SettingTexture("Tex", FolderTextures_->GetTextureIndex(CurFrame_));
	}
	
}

/// ///////////////////////////////////////////////////////////////////

GameEngineImageRenderer::GameEngineImageRenderer()
	: CutData(0, 0, 1, 1)
	, CurAnimation_(nullptr)
	//, isAnimationImageSwapped_(false)
{
}

GameEngineImageRenderer::~GameEngineImageRenderer()
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

void GameEngineImageRenderer::Start()
{
	GameEngineRenderer::Start();

	SetRenderingPipeLine("Texture");
	// 외부 텍스처를 사용할 것이니... 파이프라인은 Texture 파이프라인을 사용한다.

	ImageRendererStart();
	// 기본 상수 버퍼들의 세팅
}

void GameEngineImageRenderer::ImageRendererStart()
{
	ShaderHelper.SettingConstantBufferLink("TextureCutData", CutData);
	// 상수 버퍼 세팅 1 : 잘린 스프라이트의 경우

	ResultColor = float4::ONE;
	ShaderHelper.SettingConstantBufferLink("ResultColor", ResultColor);
	// 상수 버퍼 세팅 2 : 도출되는 색깔
}

void GameEngineImageRenderer::SetIndex(const int Index)
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


void GameEngineImageRenderer::SetImage(const std::string& _ImageName, bool _originalScale)
{
	// 애니메이션이 아닌 정적인 이미지를 세팅하는 함수
	CurTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
	// 가져온 리소스 중에 해당 이름의 텍스처가 있는지 확인한다.
	if (nullptr == CurTexture)
	{
		GameEngineDebug::MsgBoxError("존재하지 않는 텍스처를 세팅하려고 했습니다");
		return;
	}

	if (true == _originalScale)
	{
		ShaderHelper.SettingTexture("Tex", _ImageName); // Texture 렌파의 셰이더 텍스처 리소스에 해당 파일 삽입
		GameEngineTexture* FindTexture = GameEngineTextureManager::GetInst().Find(_ImageName);
		GetTransform()->SetLocalScaling({FindTexture->GetTextureSize().x, FindTexture->GetTextureSize().y, 1.0f });
	}

	ShaderHelper.SettingTexture("Tex", _ImageName);
}

void GameEngineImageRenderer::CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop /*= true*/)
{
	// 애니메이션을 만들고 컨테이너에 저장하는 함수

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

void GameEngineImageRenderer::CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop /*= true*/)
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

void GameEngineImageRenderer::SetChangeAnimation(const std::string& _Name, bool _IsForce /*= false*/)
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

void GameEngineImageRenderer::Update(float _DeltaTime)
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

void GameEngineImageRenderer::SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack)
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
void GameEngineImageRenderer::SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack)
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
void GameEngineImageRenderer::SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack)
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