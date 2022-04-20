#pragma once
#include <GameEngine/GameEngineActor.h>

class CustomSettingUIController;

class GameEngineCollision;
class GameEngineImageRenderer;
class CustomSettingUI : public GameEngineActor
{
private:
	friend CustomSettingUIController;

public:
	CustomSettingUI();
	~CustomSettingUI();
	CustomSettingUI(const CustomSettingUI& _other) = delete;
	CustomSettingUI(CustomSettingUI&& _other) noexcept;
	CustomSettingUI& operator=(const CustomSettingUI& _other) = delete; // default Copy operator 디폴트 대입 연산자
	CustomSettingUI& operator=(const CustomSettingUI&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	// 충돌체 미포함 렌더러
	GameEngineImageRenderer* clearScreen_;

	GameEngineImageRenderer* customizeNight_;

	GameEngineImageRenderer* nameFreddy_;
	GameEngineImageRenderer* portraitFreddy_;
	GameEngineImageRenderer* AILevelFreddyBanner_;

	GameEngineImageRenderer* nameBonnie_;
	GameEngineImageRenderer* portraitBonnie_;
	GameEngineImageRenderer* AILevelBonnieBanner_;

	GameEngineImageRenderer* nameChica_;
	GameEngineImageRenderer* portraitChica_;
	GameEngineImageRenderer* AILevelChicaBanner_;

	GameEngineImageRenderer* nameFoxy_;
	GameEngineImageRenderer* portraitFoxy_;
	GameEngineImageRenderer* AILevelFoxyBanner_;

	GameEngineImageRenderer* Instruction_;

	// 충돌체 포함 렌더러
	GameEngineImageRenderer* AIButtonFreddyL_;
	GameEngineCollision* AIButtonFreddyLCollision_;
	GameEngineImageRenderer* AIButtonFreddyR_;
	GameEngineCollision* AIButtonFreddyRCollision_;

	GameEngineImageRenderer* AIButtonBonnieL_;
	GameEngineCollision* AIButtonBonnieLCollision_;
	GameEngineImageRenderer* AIButtonBonnieR_;
	GameEngineCollision* AIButtonBonnieRCollision_;

	GameEngineImageRenderer* AIButtonChicaL_;
	GameEngineCollision* AIButtonChicaLCollision_;
	GameEngineImageRenderer* AIButtonChicaR_;
	GameEngineCollision* AIButtonChicaRCollision_;

	GameEngineImageRenderer* AIButtonFoxyL_;
	GameEngineCollision* AIButtonFoxyLCollision_;
	GameEngineImageRenderer* AIButtonFoxyR_;
	GameEngineCollision* AIButtonFoxyRCollision_;

	GameEngineImageRenderer* ReadyButton_;
	GameEngineCollision* ReadyButtonCollision_;

	// 이미지 교체 가능 렌더러 (= 숫자 렌더러)
	GameEngineImageRenderer* AINumberTenFreddy_;
	GameEngineImageRenderer* AINumberOneFreddy_;

	GameEngineImageRenderer* AINumberTenBonnie_;
	GameEngineImageRenderer* AINumberOneBonnie_;

	GameEngineImageRenderer* AINumberTenChica_;
	GameEngineImageRenderer* AINumberOneChica_;

	GameEngineImageRenderer* AINumberTenFoxy_;
	GameEngineImageRenderer* AINumberOneFoxy_;



private:
	void Start() override;
	void Update(float _Deltatime) override;
	void LevelCheckUpdate();

	void ImageInit();
	void CollisionInit();


	int AILevelFreddy_;
	int AILevelBonnie_;
	int AILevelChica_;
	int AILevelFoxy_;


public:
	inline int GetFreddyLevel()
	{
		return AILevelFreddy_;
	}

	inline int GetBonnieLevel()
	{
		return AILevelBonnie_;
	}

	inline int GetChicaLevel()
	{
		return AILevelChica_;
	}

	inline int GetFoxyLevel()
	{
		return AILevelFoxy_;
	}

	inline void AddFreddyLevel(int _number)
	{
		AILevelFreddy_ += _number;
	}

	inline void AddBonnieLevel(int _number)
	{
		AILevelBonnie_ += _number;
	}

	inline void AddChicaLevel(int _number)
	{
		AILevelChica_ += _number;
	}

	inline void AddFoxyLevel(int _number)
	{
		AILevelFoxy_ += _number;
	}
};

