#pragma once
#include <GameEngineBase/GameEngineSoundPlayer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameController;
class AIChica : public GameEngineActor
{
private:
	friend GameController;

public:
	AIChica(); // default constructer ����Ʈ ������
	~AIChica(); // default destructer ����Ʈ �Ҹ���
	AIChica(const AIChica& _other) = delete; // default Copy constructer ����Ʈ ���������
	AIChica(AIChica&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	AIChica& operator=(const AIChica& _other) = delete; // default Copy operator ����Ʈ ���� ������
	AIChica& operator=(const AIChica&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;
	void Update(float _DeltaTime) override;

	const float ACTION_FREQUENCY = 4.98f;
	int AILevel_;
	float deltatime_;
	bool isRecentlyMoved_;
	LOCATION curLocation_;
	LOCATION prevLocation_;

	GameEngineRandom randomGenerator_;

private:
	GameEngineSoundPlayer moveSound_;
	int soundDice_;

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
	void ActivateAction();
	void ActivateDoor();

private:
	GameEngineFSM<AIChica> state_;

#pragma region States
	StateInfo startShowStage(StateInfo _state);
	StateInfo updateShowStage(StateInfo _state);

	StateInfo startDiningArea(StateInfo _state);
	StateInfo updateDiningArea(StateInfo _state);

	StateInfo startRestRooms(StateInfo _state);
	StateInfo updateRestRooms(StateInfo _state);

	StateInfo startKitchen(StateInfo _state);
	StateInfo updateKitchen(StateInfo _state);

	StateInfo startEastHallA(StateInfo _state);
	StateInfo updateEastHallA(StateInfo _state);

	StateInfo startEastHallB(StateInfo _state);
	StateInfo updateEastHallB(StateInfo _state);

	StateInfo startROfficeDoor(StateInfo _state);
	StateInfo updateROfficeDoor(StateInfo _state);

	StateInfo startOffice(StateInfo _state);
	StateInfo updateOffice(StateInfo _state);

#pragma endregion States

};

