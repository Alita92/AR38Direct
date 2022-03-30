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
	TitleController(); // default constructer ����Ʈ ������
	~TitleController(); // default destructer ����Ʈ �Ҹ���
	TitleController(const TitleController& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleController(TitleController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	TitleController& operator=(const TitleController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleController& operator=(const TitleController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

