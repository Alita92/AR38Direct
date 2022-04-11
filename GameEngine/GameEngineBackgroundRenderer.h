#pragma once
#include "GameEngineRenderer.h"
#include <GameEngineBase\GameEngineObjectNameBase.h>

// 분류 : 
// 용도 : 

class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineBackgroundRenderer : public GameEngineRenderer
{
	struct Animation2D : public GameEngineObjectNameBase// 2D 스프라이트 애니메이션을 만들기 위한 구조체 묶음입니다.
	{
		GameEngineFolderTexture* FolderTextures_;
		GameEngineTexture* AnimationTexture_;
		float InterTime_;
		float CurTime_;

		bool IsEnd; // (애니메이션이)끝났나?
		bool Loop_; // 루프해야 하는가?
		int CurFrame_; // 현재 프레임
		int StartFrame_; // 시작 프레임
		int EndFrame_; // 끝나는 프레임

		GameEngineBackgroundRenderer* Renderer;

		std::map<int, std::vector<std::function<void()>>> FrameCallBack_;
		std::vector<std::function<void()>> EndCallBack_;
		std::vector<std::function<void()>> StartCallBack_;
		// 콜백함수는 자료구조로 관리함...
		// 프레임 콜백함수만 맵으로 관리하는 이유? 특정 프레임이 몇인지를 키값으로 할려고?

	public:
		void Reset();
		void CallStart(); // 애니메이션 시작 시에 무언가를 해 주고 싶을 때
		void CallEnd(); // 애니메이션 끝에
		void CallFrame(); // 애니메이션 특정 프레임에
		void Update(float _DeltaTime);

		void FrameUpdate();
		void ReverseFrameUpdate();
	};


public:
	GameEngineBackgroundRenderer(); // default constructer 디폴트 생성자
	~GameEngineBackgroundRenderer(); // default destructer 디폴트 소멸자
	GameEngineBackgroundRenderer(const GameEngineBackgroundRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineBackgroundRenderer(GameEngineBackgroundRenderer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameEngineBackgroundRenderer& operator=(const GameEngineBackgroundRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineBackgroundRenderer& operator=(const GameEngineBackgroundRenderer&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

	void SetImage(const std::string& _ImageName, bool _originalScale = false);
	void SetIndex(const int Index);

	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);

	void CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);

	// _IsForce 같은 애니메이션 인데도 바꿀거냐? true 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);

	inline GameEngineTexture* GetCurTexture()
	{
		return CurTexture;
	}


	inline GameEngineTexture* GetCurrentTexture()
	{
		return CurTexture;
	}

	inline std::string GetCurrentAnimationName()
	{
		return CurAnimation_->GetName();
	}

	inline bool IsCurrentAnimationString(const std::string& _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurrentAnimationPtr(const char* _Name)
	{
		return CurAnimation_->GetName() == _Name;
	}

	inline bool IsCurAnimationEnd()
	{
#ifdef _DEBUG	
		if (nullptr == CurAnimation_)
		{
			GameEngineDebug::AssertFalse();
			return false;
		}
#endif 

		return CurAnimation_->EndFrame_ == CurAnimation_->CurFrame_;
	}


	template <typename EffectType> // TODO: 나중ㅇ 람다식으로 즉석 함수만들어서 넣는 기능 추가하기
	void SetImageAnimationEndFunc(const std::string& _Name, void(EffectType::* _EndFunc)(void))
	{
		SetEndCallBack(_Name, std::bind(_EndFunc, this));
	}

	template <typename EffectType>
	void SetImageAnimationFrameFunc(const std::string& _Name, int _Index, void(EffectType::* _FrameFunc)(void))
	{
		SetFrameCallBack(_Name, _Index, std::bind(_FrameFunc, this));
	}

	inline void SetAlpha(float _Value)
	{
		ResultColor.a = _Value;
	}

	inline float GetAlpha()
	{
		return ResultColor.a;
	}

protected:
	void ImageRendererStart();
	void Update(float _DeltaTime) override;

private:
	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;

	float4 ResultColor;
	float4 CutData;
	GameEngineTexture* CurTexture;
	void Start() override;
	//bool isAnimationImageSwapped_;
};

