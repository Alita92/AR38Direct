#pragma once
#include <GameEngine/GameEngineActor.h>

class GameOverBackground;
class GameOverController : public GameEngineActor
{
public:
	GameOverController(); // default constructer ����Ʈ ������
	~GameOverController(); // default destructer ����Ʈ �Ҹ���
	GameOverController(const GameOverController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameOverController(GameOverController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	GameOverController& operator=(const GameOverController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameOverController& operator=(const GameOverController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

protected:
	GameOverBackground* gameOverBackground_;

private:
	const float WHITE_NOISE_TIME = 5.0f;
	const float SCENE_CHANGE_TIME = 5.0f;

	float deltaTime_;
	bool isWhiteNoiseOff_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

