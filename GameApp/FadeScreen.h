#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 로딩 화면이나 페이드 인 아웃 연출용으로 사용할 액터입니다.

class GameEngineUIRenderer;
class FadeScreen : public GameEngineActor
{
public:
	FadeScreen(); // default constructer 디폴트 생성자
	~FadeScreen(); // default destructer 디폴트 소멸자
	FadeScreen(const FadeScreen& _other) = delete; // default Copy constructer 디폴트 복사생성자
	FadeScreen(FadeScreen&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	FadeScreen& operator=(const FadeScreen& _other) = delete; // default Copy operator 디폴트 대입 연산자
	FadeScreen& operator=(const FadeScreen&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetAlpha(float _alpha);
	void StartFadeIn(float _time);
	void StartFadeOut(float _time);
	void SetLoadingRenderer();
	void RemoveLoadingRenderer();
	void OffScreen(float _time);
	void OnScreen();
	void Reset();
	float GetReleaseTime()
	{
		return releaseTime_;
	}
protected:
	GameEngineUIRenderer* fadeScreenRenderer_;
	GameEngineUIRenderer* loadingClockRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void ImageInit();


private:
	float deltaTime_;
	float divider_;
	float releaseTime_;
	bool isFadeIn_;
	bool isFadeOut_;
	bool isReleaseOn_;

public:

	bool isFullFadeIn_;
	bool isFullFadeOut_;
};

