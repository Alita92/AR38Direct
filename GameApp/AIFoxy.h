#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameController;
class AIFoxy : public GameEngineActor
{
public:
	AIFoxy(); // default constructer ����Ʈ ������
	~AIFoxy(); // default destructer ����Ʈ �Ҹ���
	AIFoxy(const AIFoxy& _other) = delete; // default Copy constructer ����Ʈ ���������
	AIFoxy(AIFoxy&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	AIFoxy& operator=(const AIFoxy& _other) = delete; // default Copy operator ����Ʈ ���� ������
	AIFoxy& operator=(const AIFoxy&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

