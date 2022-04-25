#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
// 분류 : 
// 용도 : 
// 설명 : 

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
	GlitchScreen(); // default constructer 디폴트 생성자
	~GlitchScreen(); // default destructer 디폴트 소멸자
	GlitchScreen(const GlitchScreen& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GlitchScreen(GlitchScreen&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GlitchScreen& operator=(const GlitchScreen& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GlitchScreen& operator=(const GlitchScreen&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

