#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameController;
class UIController : public GameEngineActor
{
private:
	friend GameController;

public:
	UIController(); // default constructer ����Ʈ ������
	~UIController(); // default destructer ����Ʈ �Ҹ���
	UIController(const UIController& _other) = delete; // default Copy constructer ����Ʈ ���������
	UIController(UIController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	UIController& operator=(const UIController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	UIController& operator=(const UIController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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
	// ������ "������" �ð��̳� ���� ��뷮�� �����ִ� �� GameController �� �� ���̴�.
	// UIController �� �� �� ��? "������ ����!"


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

