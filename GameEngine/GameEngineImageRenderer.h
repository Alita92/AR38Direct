#pragma once
#include "GameEngineRenderer.h"

// 설명 : 렌더러 중 이미지 파일을 렌더링하기 용이하게 만든 서브렌더러
//		  Start() 내부에서 렌더링 파이프라인을 돌리며, 
//		  기설정된 텍스처를 세팅해줍니다.


class GameEngineTexture;
class GameEngineFolderTexture;
class GameEngineImageRenderer : public GameEngineRenderer
{
private:
	struct Animation2D // 2D 스프라이트 애니메이션을 만들기 위한 구조체 묶음입니다.
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

		GameEngineImageRenderer* Renderer;

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

	// _IsForce 같은 애니메이션 인데도 바꿀거냐? true 바꾼다.
	void SetChangeAnimation(const std::string& _Name, bool _IsForce = false);

	void SetStartCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetEndCallBack(const std::string& _Name, std::function<void()> _CallBack);
	void SetFrameCallBack(const std::string& _Name, int _Index, std::function<void()> _CallBack);

	inline GameEngineTexture* GetCurTexture()
	{
		return CurTexture;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	std::map<std::string, Animation2D*> AllAnimations_;
	Animation2D* CurAnimation_;

	float4 CutData;
	GameEngineTexture* CurTexture;
	void Start() override;

};

