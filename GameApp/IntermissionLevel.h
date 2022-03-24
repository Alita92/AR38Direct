#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 타이틀 -> 플레이 | 플레이 레벨 간 이동 시 잠시 이동하는 레벨입니다.


class IntermissionLevel : public GameEngineLevel
{
public:
	IntermissionLevel(); // default constructer 디폴트 생성자
	~IntermissionLevel(); // default destructer 디폴트 소멸자
	IntermissionLevel(const IntermissionLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	IntermissionLevel(IntermissionLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	IntermissionLevel& operator=(const IntermissionLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	IntermissionLevel& operator=(const IntermissionLevel&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	DAY curDay_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

