#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// AIBase �� �θ� Ŭ������ ����
// ������ �ִϸ�Ʈ�δн����� AI�� �ڽ����� ������ִ� ���谡 ������?

class GameController;
class AIBonnie : public GameEngineActor
{
private:
	friend GameController;

public:
	AIBonnie(); // default constructer ����Ʈ ������
	~AIBonnie(); // default destructer ����Ʈ �Ҹ���
	AIBonnie(const AIBonnie& _other) = delete; // default Copy constructer ����Ʈ ���������
	AIBonnie(AIBonnie&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	AIBonnie& operator=(const AIBonnie& _other) = delete; // default Copy operator ����Ʈ ���� ������
	AIBonnie& operator=(const AIBonnie&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

