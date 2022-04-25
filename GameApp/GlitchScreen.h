#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
// �з� : 
// �뵵 : 
// ���� : 

class TitleController;
class IntermissionController;
class GameController;
class GameEngineImageRenderer;
class GameEngineUIRenderer;
class GlitchScreen : public GameEngineActor
{
private:
	friend TitleController;
	friend IntermissionController;
	friend GameController;

public:
	GlitchScreen(); // default constructer ����Ʈ ������
	~GlitchScreen(); // default destructer ����Ʈ �Ҹ���
	GlitchScreen(const GlitchScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	GlitchScreen(GlitchScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	GlitchScreen& operator=(const GlitchScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GlitchScreen& operator=(const GlitchScreen&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetWhiteNoiseAlpha(float _alpha);
	void PlayWhiteNoise(bool _on);
	void SetStatic();
	void PlayAwakeScanLine();
	void PlayAwakeScanLineFast();

	void SetSubRenderer(bool _on);

protected:
	GameEngineUIRenderer* whiteNoiseRenderer_;
	GameEngineUIRenderer* scanLineRenderer_;
	GameEngineUIRenderer* subScanLineRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void ImageInit();
	void ScanLineRandomChange();
	void RandomImageChange();
	const float SCANLINE_DOWNSPEED = 40.0f;

	float generalInterTime_;
	float changeInterTime_;
	int timeDice_;
	int changeDice_;
	bool isFirstSessionOut_;
	GameEngineRandom randomGenerator_;

	bool isStatic_;
};

