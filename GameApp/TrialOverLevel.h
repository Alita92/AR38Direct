#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

class TrialOverLevel : public GameEngineLevel
{
private:
	 friend class TrialOverController;

public:
	TrialOverLevel(); // default constructer 디폴트 생성자
	~TrialOverLevel(); // default destructer 디폴트 소멸자
	TrialOverLevel(const TrialOverLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TrialOverLevel(TrialOverLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	TrialOverLevel& operator=(const TrialOverLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TrialOverLevel& operator=(const TrialOverLevel&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	TrialOverController* controller_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

