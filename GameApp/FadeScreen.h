#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : �ε� ȭ���̳� ���̵� �� �ƿ� ��������� ����� �����Դϴ�.

class GameEngineUIRenderer;
class FadeScreen : public GameEngineActor
{
public:
	FadeScreen(); // default constructer ����Ʈ ������
	~FadeScreen(); // default destructer ����Ʈ �Ҹ���
	FadeScreen(const FadeScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	FadeScreen(FadeScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	FadeScreen& operator=(const FadeScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	FadeScreen& operator=(const FadeScreen&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

