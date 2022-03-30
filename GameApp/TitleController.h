#pragma once
#include <GameEngine/GameEngineActor.h>

class TitleFreddy;
class TitleText;
class TitleNewsPaper;
class GameEngineCollision;
class TitleController : public GameEngineActor
{
private:
	friend TitleFreddy;
	friend TitleText;
	friend TitleNewsPaper;

public:
	TitleController(); // default constructer 디폴트 생성자
	~TitleController(); // default destructer 디폴트 소멸자
	TitleController(const TitleController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleController(TitleController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	TitleController& operator=(const TitleController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleController& operator=(const TitleController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	TitleFreddy* titleFreddy_;
	TitleText* titleText_;
	TitleNewsPaper* titleNewsPaper_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void CollisionNewGame(GameEngineCollision* _other);
	void CollisionContinue(GameEngineCollision* _other);
	void CollisionCustomNight(GameEngineCollision* _other);

private:
	void ActorInit();
};

