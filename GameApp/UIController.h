#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineImageRenderer;
class GameController;
class UIController : public GameEngineActor
{
private:
	friend GameController;

public:
	UIController(); // default constructer 디폴트 생성자
	~UIController(); // default destructer 디폴트 소멸자
	UIController(const UIController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	UIController& operator=(const UIController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	UIController& operator=(const UIController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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
	// CCTV 모드 전용 렌더링?
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
	// 어차피 "실제로" 시간이나 전력 사용량을 돌려주는 건 GameController 가 할 일이다.
	// UIController 가 해 줄 것? "렌더링 변경!"

	bool powerRateTenFlag_;
	bool powerRateOneFlag_;

	float deltaTime_;

private:
	void ImageInit();
	void CollisionInit();
	void StateInit();
	void DebugRenderUpdate();


private: // FSM 은 기성 시스템을 가져왔으나 선생님이 새로 만드실 경우 리팩토링을 염두에 둡니다.
	GameEngineFSM<UIController> state_;

#pragma region States
		StateInfo startOfficeUI(StateInfo _state);
		StateInfo updateOfficeUI(StateInfo _state);

		StateInfo startCCTVUI(StateInfo _state);
		StateInfo updateCCTVUI(StateInfo _state);
#pragma endregion States
};

