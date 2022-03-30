#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// 분류 : 
// 용도 : 
// 설명 :
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
	// 띄우기만 하면 됨
	GameEngineImageRenderer* titleName_;
	GameEngineImageRenderer* titleScott_;

	// 충돌체 있어야 함
	GameEngineImageRenderer* titleNewGame_;
	GameEngineCollision* titleNewGameCollision_;
	GameEngineImageRenderer* titleContinue_;
	GameEngineCollision* titleContinueCollision_;
	GameEngineImageRenderer* title6thNight_;
	GameEngineCollision* title6thNightCollision_;
	GameEngineImageRenderer* titleCustomNight_;
	GameEngineCollision* titleCustomNightCollision_;


	void ImageInit();
	void CollisionInit();

private:
	void Start() override;
	void Update(float _Deltatime) override;
	void DebugRenderUpdate();
	void CollisionCheckUpdate();

private:
	void CollisionNewGame(GameEngineCollision* _other);
	void CollisionContinue(GameEngineCollision* _other);
	void CollisionCustomNight(GameEngineCollision* _other);
};

