#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

class TitleLevel;
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
	friend TitleLevel;
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
	// SOUND PLAYER
	GameEngineSoundPlayer musicPlayer_;
	GameEngineSoundPlayer ambientPlayer_;
	GameEngineSoundPlayer awakePlayer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void CollisionNewGame(GameEngineCollision* _other);
	void CollisionContinue(GameEngineCollision* _other);
	void CollisionCustomNight(GameEngineCollision* _other);

	void CollisionNewDataYes(GameEngineCollision* _other);
	void CollisionNewDataNo(GameEngineCollision* _other);

private:
	void ActorInit();
	void StateInit();

	void ControllerReloading();

private:
	void UpdateTitleAlphaChange();
	void DebugRenderUpdate();
public:
	void StopAllSound()
	{
		musicPlayer_.Stop();
		ambientPlayer_.Stop();
		awakePlayer_.Stop();
	}

private:
	float deltaTime_;
	float alphaChangeTime_;
	bool isDark_;
	bool isDebugOn_;
private:
	GameEngineFSM<TitleController> state_;

#pragma region States
	StateInfo startSceneReady(StateInfo _state);
	StateInfo updateSceneReady(StateInfo _state);

	StateInfo startIdle(StateInfo _state);
	StateInfo updateIdle(StateInfo _state);

	StateInfo startNewData(StateInfo _state);
	StateInfo updateNewData(StateInfo _state);

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

