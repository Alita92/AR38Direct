#pragma once
#include <GameEngine/GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class UIController : public GameEngineActor
{
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

	GameEngineUIRenderer* muteCallRenderer_;

	GameEngineUIRenderer* nightTypoRenderer_;
	GameEngineUIRenderer* nightNumRenderer_;

	GameEngineUIRenderer* powerLeftTypoRenderer_;
	GameEngineUIRenderer* powerLeftHundredRenderer_;
	GameEngineUIRenderer* powerLeftTenRenderer_;
	GameEngineUIRenderer* powerLeftOneRenderer_;
	GameEngineUIRenderer* powerLeftPercentageRenderer_;

	GameEngineUIRenderer* powerUsageTypoRenderer_;
	GameEngineUIRenderer* powerUsageLevelRenderer_;


private:
	void Start() override;

private:
	void ImageInit();
};

