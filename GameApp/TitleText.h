#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// �з� : 
// �뵵 : 
// ���� :
class GameEngineImageRenderer;
class TitleText : public GameEngineActor
{
public:
	TitleText(); 
	~TitleText();
	TitleText(const TitleText& _other) = delete;
	TitleText(TitleText&& _other) noexcept;
	TitleText& operator=(const TitleText& _other) = delete;
	TitleText& operator=(const TitleText&& _other) noexcept = delete;

protected:
	// ���⸸ �ϸ� ��
	GameEngineImageRenderer* titleName_;
	GameEngineImageRenderer* titleScott_;

	// �浹ü �־�� ��
	GameEngineImageRenderer* titleNewGame_;
	GameEngineImageRenderer* titleContinue_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

