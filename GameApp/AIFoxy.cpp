#include "PreCompile.h"
#include "AIFoxy.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "ENUM.h"

AIFoxy::AIFoxy() // default constructer ����Ʈ ������
	:AILevel_(0), deltatime_(0.0f), state_(this), isDoorLocked_(false), isPlayerStares_(false), level_(FOXYLEVEL::MAX)
{

}

AIFoxy::~AIFoxy() // default destructer ����Ʈ �Ҹ���
{

}


void AIFoxy::InitState()
{
	state_.CreateState("Lv1", &AIFoxy::startLv1, &AIFoxy::updateLv1);
	state_.CreateState("Lv2", &AIFoxy::startLv2, &AIFoxy::updateLv2);
	state_.CreateState("Lv3", &AIFoxy::startLv3, &AIFoxy::updateLv3);
	state_.CreateState("Lv4", &AIFoxy::startLv4, &AIFoxy::updateLv4);

	state_.ChangeState("Lv1");
}

void AIFoxy::Reloading()
{
	deltatime_ = 0.0f;
	level_ = FOXYLEVEL::MAX;
	isDoorLocked_ = false;
	isPlayerStares_ = false;
	state_.ChangeState("Lv1");
}

void AIFoxy::Start()
{
	InitState();
}

void AIFoxy::Update(float _DeltaTime)
{
	state_.Update();
}

void AIFoxy::SetAILevel(int _level)
{
	AILevel_ = _level;
	return;
}

void AIFoxy::AddAILevel(int _level)
{
	AILevel_ += _level;
	return;
}

StateInfo AIFoxy::startLv1(StateInfo _state)
{
	deltatime_ = 0.0f;
	level_ = FOXYLEVEL::LV1;
	return StateInfo();
}

StateInfo AIFoxy::updateLv1(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		if (true == isPlayerStares_)
		{
			// �������� �ϴµ� �÷��̾ CCTV�� ���� �ִ�?
			// �����̴� �� ������ �����ϰ� 0.8 ~ 16.7�� ������ ����¡ �ð��� ������ �˴ϴ�.
			deltatime_ = (randomGenerator_.RandomFloat(0.8f, 16.7f) * -1.0f);
			return StateInfo();
		}

		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			return "Lv2";
		}
	}

	return StateInfo();
}

StateInfo AIFoxy::startLv2(StateInfo _state)
{
	deltatime_ = 0.0f;
	level_ = FOXYLEVEL::LV2;
	return StateInfo();
}

StateInfo AIFoxy::updateLv2(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		if (true == isPlayerStares_)
		{
			// �������� �ϴµ� �÷��̾ CCTV�� ���� �ִ�?
			// �����̴� �� ������ �����ϰ� 0.8 ~ 16.7�� ������ ����¡ �ð��� ������ �˴ϴ�.
			deltatime_ = (randomGenerator_.RandomFloat(0.8f, 16.7f) * -1.0f);
			return StateInfo();
		}

		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			return "Lv3";
		}
	}

	return StateInfo();
}

StateInfo AIFoxy::startLv3(StateInfo _state)
{
	deltatime_ = 0.0f;
	level_ = FOXYLEVEL::LV3;

	return StateInfo();
}

StateInfo AIFoxy::updateLv3(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		if (true == isPlayerStares_)
		{
			// �������� �ϴµ� �÷��̾ CCTV�� ���� �ִ�?
			// �����̴� �� ������ �����ϰ� 0.8 ~ 16.7�� ������ ����¡ �ð��� ������ �˴ϴ�.
			deltatime_ = (randomGenerator_.RandomFloat(0.8f, 16.7f) * -1.0f);
			return StateInfo();
		}

		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			return "Lv4";
		}
	}

	return StateInfo();
}

StateInfo AIFoxy::startLv4(StateInfo _state)
{
	deltatime_ = 0.0f;
	level_ = FOXYLEVEL::LV4;

	return StateInfo();
}

StateInfo AIFoxy::updateLv4(StateInfo _state)
{
	// �̹� ���ô� ���̷� �ں긦 ���� ���·�,
	// �� ���ķκ��� CCTV�� ���� ���� �ǹ̰� �����ϴ�.
	// �ٸ� �� ���� WESTHALLA CCTV �� ���� ���ð� �پ���� �ִϸ��̼��� ����մϴ�.

	return StateInfo();
}

void AIFoxy::ResetFoxyLevel()
{
	state_.ChangeState("Lv1");
}

void AIFoxy::ActivateJumpscare()
{
	if (true == state_.IsCurStateName("Lv4"))
	{
		return;
	}

	state_.ChangeState("Lv4");
}