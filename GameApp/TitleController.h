#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

class GameMouse;
class GlitchScreen;
class FadeScreen;
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
	friend GlitchScreen;

public:
	TitleController(); // default constructer ����Ʈ ������
	~TitleController(); // default destructer ����Ʈ �Ҹ���
	TitleController(const TitleController& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleController(TitleController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	TitleController& operator=(const TitleController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleController& operator=(const TitleController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	const float SCENE_CHANGE_TIME = 5.0f;

protected:
	GlitchScreen* glitchScreen_;
	FadeScreen* fadeScreen_;
	GameMouse* titleMouse_;
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
	void StateInit();

private:
	void UpdateTitleAlphaChange();

private:
	float deltaTime_;
	float alphaChangeTime_;

private: // FSM �� �⼺ �ý����� ���������� �������� ���� ����� ��� �����丵�� ���ο� �Ӵϴ�.
	GameEngineFSM<TitleController> state_;

#pragma region States
	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startNewGame(StateInfo _state);
	StateInfo updateNewGame(StateInfo _state);

	StateInfo startContinue(StateInfo _state);
	StateInfo updateContinue(StateInfo _state);

	StateInfo startCustomNight(StateInfo _state);
	StateInfo updateCustomNight(StateInfo _state);

	StateInfo start6thNight(StateInfo _state);
	StateInfo update6thNight(StateInfo _state);
#pragma endregion States
};

