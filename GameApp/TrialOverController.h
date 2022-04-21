#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include "ENUM.h"

class GameEngineImageRenderer;
class FadeScreen;
class TrialOverController : public GameEngineActor
{
private:
	friend class TrialOverLevel;

public:
	TrialOverController(); // default constructer ����Ʈ ������
	~TrialOverController(); // default destructer ����Ʈ �Ҹ���
	TrialOverController(const TrialOverController& _other) = delete; // default Copy constructer ����Ʈ ���������
	TrialOverController(TrialOverController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	TrialOverController& operator=(const TrialOverController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TrialOverController& operator=(const TrialOverController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	FadeScreen* fadeScreen_;
	GameEngineImageRenderer* trialOverBackground_;
	GameEngineSoundPlayer ambientPlayer_;

private:
	void InitImage();
	void Reloading();

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	bool isFadeIn_;
	bool isLevelChanged_;
};

