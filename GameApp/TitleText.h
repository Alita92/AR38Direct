#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// �з� : 
// �뵵 : 
// ���� :
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineImageRenderer;
class TitleController;
class TitleText : public GameEngineActor
{
	friend TitleController;

private:

public:
	TitleText();
	~TitleText();
	TitleText(const TitleText& _other) = delete;
	TitleText(TitleText&& _other) noexcept;
	TitleText& operator=(const TitleText& _other) = delete;
	TitleText& operator=(const TitleText&& _other) noexcept = delete;

protected:
	// ���⸸ �ϸ� ��
	GameEngineUIRenderer* titleName_;
	GameEngineUIRenderer* titleScott_;
	GameEngineUIRenderer* titleArrow_;
	GameEngineUIRenderer* titleNewData_;

	// �浹ü �־�� ��
	GameEngineUIRenderer* titleNewGame_;
	GameEngineCollision* titleNewGameCollision_;
	GameEngineUIRenderer* titleContinue_;
	GameEngineCollision* titleContinueCollision_;
	GameEngineUIRenderer* title6thNight_;
	GameEngineCollision* title6thNightCollision_;
	GameEngineUIRenderer* titleCustomNight_;
	GameEngineCollision* titleCustomNightCollision_;

	GameEngineUIRenderer* titleYes_;
	GameEngineCollision* titleYesCollision_;

	GameEngineUIRenderer* titleNo_;
	GameEngineCollision* titleNoCollision_;
	


	void ImageInit();
	void CollisionInit();

private:
	void Start() override;
	void Update(float _Deltatime) override;
	void DebugRenderUpdate();
};

