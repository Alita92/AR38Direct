#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"
// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineImageRenderer;
class GameController;
class UIController : public GameEngineActor
{
private:
	friend GameController;

public:
	UIController(); // default constructer ����Ʈ ������
	~UIController(); // default destructer ����Ʈ �Ҹ���
	UIController(const UIController& _other) = delete; // default Copy constructer ����Ʈ ���������
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	UIController& operator=(const UIController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UIController& operator=(const UIController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* foxyRunningRenderer_;
	GameEngineUIRenderer* CCTVAnimationRenderer_;
	GameEngineImageRenderer* CCTVRealRenderer_;

	GameEngineUIRenderer* timeTenRenderer_;
	GameEngineUIRenderer* timeOneRenderer_;
	GameEngineUIRenderer* amRenderer_;

	GameEngineUIRenderer* CCTVButtonRenderer_;
	GameEngineCollision* CCTVButtonCollision_;

	GameEngineUIRenderer* muteCallRenderer_;
	GameEngineCollision* muteCallCollision_;

	GameEngineUIRenderer* nightTypoRenderer_;
	GameEngineUIRenderer* nightNumRenderer_;

	GameEngineUIRenderer* powerRateTypoRenderer_;
	GameEngineUIRenderer* powerRateHundredRenderer_;
	GameEngineUIRenderer* powerRateTenRenderer_;
	GameEngineUIRenderer* powerRateOneRenderer_;
	GameEngineUIRenderer* powerRatePercentageRenderer_;

	GameEngineUIRenderer* powerLevelTypoRenderer_;
	GameEngineUIRenderer* powerLevelRenderer_;

protected:
	// CCTV ��� ���� ������?
	GameEngineUIRenderer* cameraDisabledRenderer_;
	GameEngineUIRenderer* recordingMarkRenderer_;
	GameEngineUIRenderer* cameraNameRenderer_;
	GameEngineUIRenderer* mapRenderer_;

	GameEngineUIRenderer* cam1AScreenRenderer_;
	GameEngineUIRenderer* cam1ARenderer_;
	GameEngineCollision* cam1ACollision_;

	GameEngineUIRenderer* cam1BScreenRenderer_;
	GameEngineUIRenderer* cam1BRenderer_;
	GameEngineCollision* cam1BCollision_;

	GameEngineUIRenderer* cam1CScreenRenderer_;
	GameEngineUIRenderer* cam1CRenderer_;
	GameEngineCollision* cam1CCollision_;

	GameEngineUIRenderer* cam5ScreenRenderer_;
	GameEngineUIRenderer* cam5Renderer_;
	GameEngineCollision* cam5Collision_;

	GameEngineUIRenderer* cam3ScreenRenderer_;
	GameEngineUIRenderer* cam3Renderer_;
	GameEngineCollision* cam3Collision_;

	GameEngineUIRenderer* cam2AScreenRenderer_;
	GameEngineUIRenderer* cam2ARenderer_;
	GameEngineCollision* cam2ACollision_;

	GameEngineUIRenderer* cam2BScreenRenderer_;
	GameEngineUIRenderer* cam2BRenderer_;
	GameEngineCollision* cam2BCollision_;

	GameEngineUIRenderer* cam7ScreenRenderer_;
	GameEngineUIRenderer* cam7Renderer_;
	GameEngineCollision* cam7Collision_;

	GameEngineUIRenderer* cam6ScreenRenderer_;
	GameEngineUIRenderer* cam6Renderer_;
	GameEngineCollision* cam6Collision_;

	GameEngineUIRenderer* cam4AScreenRenderer_;
	GameEngineUIRenderer* cam4ARenderer_;
	GameEngineCollision* cam4ACollision_;

	GameEngineUIRenderer* cam4BScreenRenderer_;
	GameEngineUIRenderer* cam4BRenderer_;
	GameEngineCollision* cam4BCollision_;

private:
	GameEngineCollision* mouseLeftCollision_;
	GameEngineCollision* mouseRightCollision_;

protected:
	const float DAYPASS_X_FLOAT = 70.0f;
	GameEngineUIRenderer* dayPassHiderUpper_;
	GameEngineUIRenderer* dayPassHiderBottom_;
	GameEngineUIRenderer* dayPassNum5_;
	GameEngineUIRenderer* dayPassNum6_;
	GameEngineUIRenderer* dayPassAM_;


private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetTimeRenderer(int _curTime);
	void SetPowerRateRenderer(float _curPowerRate);
	void SetPowerLevelRenderer(int _curPowerLevel);
	void SetCCTVNameRenderer(LOCATION _location);
	void SetCCTVScreenHighlight(LOCATION _location);
	void SetCCTVScreenLowlight(LOCATION _location);
	void SetNightTypo(DAY _day);
	void SwitchUIState(PLAYERSTATUS _playerStatus);


private:
	// ������ "������" �ð��̳� ���� ��뷮�� �����ִ� �� GameController �� �� ���̴�.
	// UIController �� �� �� ��? "������ ����!"

	bool powerRateTenFlag_;
	bool powerRateOneFlag_;

	float deltaTime_;

private:
	void ImageInit();
	void CollisionInit();
	void StateInit();
	void DebugRenderUpdate();


private: // FSM �� �⼺ �ý����� ���������� �������� ���� ����� ��� �����丵�� ���ο� �Ӵϴ�.
	GameEngineFSM<UIController> state_;

#pragma region States
		StateInfo startOfficeUI(StateInfo _state);
		StateInfo updateOfficeUI(StateInfo _state);

		StateInfo startCCTVUI(StateInfo _state);
		StateInfo updateCCTVUI(StateInfo _state);
#pragma endregion States
};

