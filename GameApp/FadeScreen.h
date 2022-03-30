#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : �ε� ȭ���̳� ���̵� �� �ƿ� ��������� ����� �����Դϴ�.

class GameEngineImageRenderer;
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
	void SetStartAlpha(float _alpha);
	void StartFadeIn(float _time);
	void StartFadeOut(float _time);
	void SetLoadingRenderer();
	void ReleaseScreen(float _time);

protected:
	GameEngineImageRenderer* fadeScreenRenderer_;
	GameEngineImageRenderer* loadingClockRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void ImageInit();

private:
	float deltaTime_;
	float divider_;
	bool isFadeIn_;
	bool isFadeOut_;

public:

	bool isFullFadeIn_;
	bool isFullFadeOut_;
};

