#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 
class CustomSettingController;
class CustomSettingLevel : public GameEngineLevel
{
public:
	CustomSettingLevel(); 
	~CustomSettingLevel();
	CustomSettingLevel(const CustomSettingLevel& _other) = delete;
	CustomSettingLevel(CustomSettingLevel&& _other) noexcept;
	CustomSettingLevel& operator=(const CustomSettingLevel& _other) = delete;
	CustomSettingLevel& operator=(const CustomSettingLevel&& _other) noexcept = delete;

protected:
	CustomSettingController* controller_;

private:
	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent() override;
	void LevelChangeStartEvent() override;
};

