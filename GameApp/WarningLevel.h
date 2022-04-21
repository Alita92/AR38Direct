#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
// 설명 : 

class WarningController;
class GameEngineImageRenderer;
class WarningLevel : public GameEngineLevel
{
private:
	friend class WarningController;

public:
	WarningLevel(); // default constructer 디폴트 생성자
	~WarningLevel(); // default destructer 디폴트 소멸자
	WarningLevel(const WarningLevel& _other) = delete; // default Copy constructer 디폴트 복사생성자
	WarningLevel(WarningLevel&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	WarningLevel& operator=(const WarningLevel& _other) = delete; // default Copy operator 디폴트 대입 연산자
	WarningLevel& operator=(const WarningLevel&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;

private:
	WarningController* controller_;

};

