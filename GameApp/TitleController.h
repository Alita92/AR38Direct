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
	TitleController(); // default constructer 디폴트 생성자
	~TitleController(); // default destructer 디폴트 소멸자
	TitleController(const TitleController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleController(TitleController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	TitleController& operator=(const TitleController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleController& operator=(const TitleController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

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

private: // FSM 은 기성 시스템을 가져왔으나 선생님이 새로 만드실 경우 리팩토링을 염두에 둡니다.
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

