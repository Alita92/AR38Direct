#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GameEngineImageRenderer;
class CustomSettingUI : public GameEngineActor
{
public:
	CustomSettingUI();
	~CustomSettingUI();
	CustomSettingUI(const CustomSettingUI& _other) = delete;
	CustomSettingUI(CustomSettingUI&& _other) noexcept;
	CustomSettingUI& operator=(const CustomSettingUI& _other) = delete; // default Copy operator ����Ʈ ���� ������
	CustomSettingUI& operator=(const CustomSettingUI&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	// �浹ü ������ ������
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

	// �浹ü ���� ������
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

	// �̹��� ��ü ���� ������ (= ���� ������)
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
	void DebugRenderUpdate();
	void CollisionCheckUpdate();

	void ImageInit();
	void CollisionInit();

private:
	void CollisionAIButtonFreddyL(GameEngineCollision* _other);
	void CollisionAIButtonFreddyR(GameEngineCollision* _other);

	void CollisionAIButtonBonnieL(GameEngineCollision* _other);
	void CollisionAIButtonBonnieR(GameEngineCollision* _other);

	void CollisionAIButtonChicaL(GameEngineCollision* _other);
	void CollisionAIButtonChicaR(GameEngineCollision* _other);

	void CollisionAIButtonFoxyL(GameEngineCollision* _other);
	void CollisionAIButtonFoxyR(GameEngineCollision* _other);

	void CollisionReadyButton(GameEngineCollision* _other);

private:
	int AILevelFreddy_;
	int AILevelBonnie_;
	int AILevelChica_;
	int AILevelFoxy_;
};

