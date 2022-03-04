#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameController : public GameEngineActor
{
private:	// member Var

public:
	GameController(); // default constructer 디폴트 생성자
	~GameController(); // default destructer 디폴트 소멸자
	GameController(const GameController& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameController(GameController&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	GameController& operator=(const GameController& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameController& operator=(const GameController&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitState();

private:
#pragma region States
	//StateInfo startIdle(StateInfo _state);
	//StateInfo updateIdle(StateInfo _state);
	//
	//StateInfo startCCTV(StateInfo _state);
	//StateInfo updateCCTV(StateInfo _state);
};

