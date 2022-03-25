#pragma once
#include <GameEngine/GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class UIController : public GameEngineActor
{
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

