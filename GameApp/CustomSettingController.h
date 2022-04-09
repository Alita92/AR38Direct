#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include <GameEngineBase/GameEngineRandom.h>


// �з� : 
// �뵵 : 
// ���� : 
class CustomSettingLevel;
class CustomSettingUI;
class GameMouse;
class CustomSettingController : public GameEngineActor
{
private:	// member Var
	friend CustomSettingLevel;
	friend CustomSettingUI;

public:
	CustomSettingController(); // default constructer ����Ʈ ������
	~CustomSettingController(); // default destructer ����Ʈ �Ҹ���
	CustomSettingController(const CustomSettingController& _other) = delete; // default Copy constructer ����Ʈ ���������
	CustomSettingController(CustomSettingController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	CustomSettingController& operator=(const CustomSettingController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	CustomSettingController& operator=(const CustomSettingController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

