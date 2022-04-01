#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameController;
class AIFoxy : public GameEngineActor
{
public:
	AIFoxy(); // default constructer 디폴트 생성자
	~AIFoxy(); // default destructer 디폴트 소멸자
	AIFoxy(const AIFoxy& _other) = delete; // default Copy constructer 디폴트 복사생성자
	AIFoxy(AIFoxy&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	AIFoxy& operator=(const AIFoxy& _other) = delete; // default Copy operator 디폴트 대입 연산자
	AIFoxy& operator=(const AIFoxy&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

	const float ACTION_FREQUENCY = 5.01f;
	int AILevel_;
	float deltatime_;

	GameEngineRandom randomGenerator_;

	FOXYLEVEL level_;

public:
	void SetAILevel(int _level);
	void AddAILevel(int _level);
	void InitState();

	FOXYLEVEL GetFoxyLevel()
	{
		return level_;
	}

	bool isDoorLocked_;
	bool isPlayerStares_;

public:
	void ResetFoxyLevel();

private:
	GameEngineFSM<AIFoxy> state_;

#pragma region States
	StateInfo startLv1(StateInfo _state);
	StateInfo updateLv1(StateInfo _state);

	StateInfo startLv2(StateInfo _state);
	StateInfo updateLv2(StateInfo _state);

	StateInfo startLv3(StateInfo _state);
	StateInfo updateLv3(StateInfo _state);

	StateInfo startLv4(StateInfo _state);
	StateInfo updateLv4(StateInfo _state);
#pragma endregion States

};

