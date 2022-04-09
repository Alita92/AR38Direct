#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>


// 분류 : 
// 용도 : 
// 설명 : 
class CustomSettingLevel;
class CustomSettingUI;
class GameMouse;
class CustomSettingController : public GameEngineActor
{
private:	// member Var
	friend CustomSettingLevel;
	friend CustomSettingUI;

public:
	CustomSettingController(); // default constructer 디폴트 생성자
	~CustomSettingController(); // default destructer 디폴트 소멸자
	CustomSettingController(const CustomSettingController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	CustomSettingController(CustomSettingController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	CustomSettingController& operator=(const CustomSettingController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	CustomSettingController& operator=(const CustomSettingController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	CustomSettingUI* customSettingUI_;
	GameMouse* settingMouse_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void ActorInit();
	void Reloading();

private:
	void CollisionFreddyLvUp(GameEngineCollision* _other);
	void CollisionFreddyLvDown(GameEngineCollision* _other);
	void CollisionBonnieLvUp(GameEngineCollision* _other);
	void CollisionBonnieLvDown(GameEngineCollision* _other);
	void CollisionChicaLvUp(GameEngineCollision* _other);
	void CollisionChicaLvDown(GameEngineCollision* _other);
	void CollisionFoxyLvUp(GameEngineCollision* _other);
	void CollisionFoxyLvDown(GameEngineCollision* _other);
	void CollisionReady(GameEngineCollision* _other);
};

