#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// AIBase 로 부모 클래스를 만들어서
// 나머지 애니매트로닉스들의 AI를 자식으로 상속해주는 설계가 좋을까?

class GameController;
class AIBonnie : public GameEngineActor
{
private:
	friend GameController;

public:
	AIBonnie(); // default constructer 디폴트 생성자
	~AIBonnie(); // default destructer 디폴트 소멸자
	AIBonnie(const AIBonnie& _other) = delete; // default Copy constructer 디폴트 복사생성자
	AIBonnie(AIBonnie&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	AIBonnie& operator=(const AIBonnie& _other) = delete; // default Copy operator 디폴트 대입 연산자
	AIBonnie& operator=(const AIBonnie&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;
	void Update(float _DeltaTime) override;

	const float ACTION_FREQUENCY = 4.97f;
	int AILevel_;
	float deltatime_;
	bool isRecentlyMoved_;
	LOCATION curLocation_;
	LOCATION prevLocation_;
	
	GameEngineRandom randomGenerator_;

private:
	GameEngineSoundPlayer moveSound_;

public:
	void SetAILevel(int _level);
	void AddAILevel(int _level);
	void InitState();
	void Reloading();

	LOCATION GetLocation()
	{
		return curLocation_;
	}

	LOCATION GetPrevLocation()
	{
		return prevLocation_;
	}

	bool isDoorLocked_;
	bool isPlayerStares_;

	void ActivateJumpscare();

private:
	GameEngineFSM<AIBonnie> state_;

#pragma region States
	StateInfo startShowStage(StateInfo _state);
	StateInfo updateShowStage(StateInfo _state);

	StateInfo startBackStage(StateInfo _state);
	StateInfo updateBackStage(StateInfo _state);

	StateInfo startDiningArea(StateInfo _state);
	StateInfo updateDiningArea(StateInfo _state);

	StateInfo startWestHallA(StateInfo _state);
	StateInfo updateWestHallA(StateInfo _state);

	StateInfo startWestHallB(StateInfo _state);
	StateInfo updateWestHallB(StateInfo _state);
	
	StateInfo startSupplyCloset(StateInfo _state);
	StateInfo updateSupplyCloset(StateInfo _state);

	StateInfo startLOfficeDoor(StateInfo _state);
	StateInfo updateLOfficeDoor(StateInfo _state);
	
	StateInfo startOffice(StateInfo _state);
	StateInfo updateOffice(StateInfo _state);

#pragma endregion States


};

