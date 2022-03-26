#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
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



private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetTimeRenderer(int _curTime);
	void SetPowerRateRenderer(float _curPowerRate);
	void SetPowerLevelRenderer(int _curPowerLevel);

private:
	// 어차피 "실제로" 시간이나 전력 사용량을 돌려주는 건 GameController 가 할 일이다.
	// UIController 가 해 줄 것? "렌더링 변경!"


	bool powerRateTenFlag_;
	bool powerRateOneFlag_;

private:
	void ImageInit();
	void CollisionInit();
	void DebugRenderUpdate();
	void CollisionCheckUpdate();

private:
	void CollisionCCTVButton(GameEngineCollision* _other);
	void CollisionMuteCall(GameEngineCollision* _other);

};

