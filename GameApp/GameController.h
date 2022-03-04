#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameController : public GameEngineActor
{
private:	// member Var

public:
	GameController(); // default constructer ����Ʈ ������
	~GameController(); // default destructer ����Ʈ �Ҹ���
	GameController(const GameController& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameController(GameController&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	GameController& operator=(const GameController& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameController& operator=(const GameController&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

