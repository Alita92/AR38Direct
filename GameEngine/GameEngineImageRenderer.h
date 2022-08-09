#pragma once
#include "GameEngineRenderer.h"
#include <GameEngineBase\GameEngineObjectNameBase.h>

// ���� : ������ �� �̹��� ������ �������ϱ� �����ϰ� ���� ���귻����
//		  Start() ���ο��� ������ ������������ ������, 
//		  �⼳���� �ؽ�ó�� �������ݴϴ�.



class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D : public GameEngineObjectNameBase// 2D ��������Ʈ �ִϸ��̼��� ����� ���� ����ü �����Դϴ�.
	{
		GameEngineFolderTexture* FolderTextures_;
		GameEngineTexture* AnimationTexture_;
		float InterTime_;
		float CurTime_;

		bool IsEnd; // (�ִϸ��̼���)������?
		bool Loop_; // �����ؾ� �ϴ°�?
		int CurFrame_; // ���� ������
		int StartFrame_; // ���� ������
		int EndFrame_; // ������ ������

		GameEngineImageRenderer* Renderer;

		std::map<int, std::vector<std::function<void()>>> FrameCallBack_; 
		std::vector<std::function<void()>> EndCallBack_;
		std::vector<std::function<void()>> StartCallBack_;
		// �ݹ��Լ��� �ڷᱸ���� ������...
		// ������ �ݹ��Լ��� ������ �����ϴ� ����? Ư�� �������� �������� Ű������ �ҷ���?

	public:
		void Reset();
		void CallStart(); // �ִϸ��̼� ���� �ÿ� ���𰡸� �� �ְ� ���� ��
		void CallEnd(); // �ִϸ��̼� ����
		void CallFrame(); // �ִϸ��̼� Ư�� �����ӿ�
		void Update(float _DeltaTime);

		void FrameUpdate();
		void ReverseFrameUpdate();
	};
	
public:
	// constrcuter destructer
	GameEngineImageRenderer();
	~GameEngineImageRenderer();

	// delete Function
	GameEngineImageRenderer(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer(GameEngineImageRenderer&& _Other) noexcept = delete;
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _Other) = delete;
	GameEngineImageRenderer& operator=(GameEngineImageRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _ImageName, bool _originalScale = false);
	void SetIndex(const int Index);

	void CreateAnimation(const std::string& _TextureName, const std::string& _Name, int _StartFrame, int _EndFrame, float _InterTime, bool _Loop = true);

	void CreateAnimationFolder(const std::string& _Name, const std::string& _FolderTexName, float _InterTime, bool _Loop = true);

	// _IsForce ���� �ִϸ��̼� �ε��� �ٲܰų�? true �ٲ۴�.
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


	template <typename EffectType> // TODO: ���ߤ� ���ٽ����� �Ｎ �Լ����� �ִ� ��� �߰��ϱ�
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

