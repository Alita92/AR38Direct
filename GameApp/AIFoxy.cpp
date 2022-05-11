#include "PreCompile.h"
#include "AIFoxy.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "ENUM.h"

AIFoxy::AIFoxy() // default constructer 디폴트 생성자
	:AILevel_(0), deltatime_(0.0f), state_(this), isDoorLocked_(false), isPlayerStares_(false), level_(FOXYLEVEL::MAX)
{

}

AIFoxy::~AIFoxy() // default destructer 디폴트 소멸자
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
			// 나갈려고 하는데 플레이어가 CCTV를 보고 있다?
			// 움직이는 데 무조건 실패하고 0.8 ~ 16.7초 동안의 프리징 시간을 가지게 됩니다.
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
			// 나갈려고 하는데 플레이어가 CCTV를 보고 있다?
			// 움직이는 데 무조건 실패하고 0.8 ~ 16.7초 동안의 프리징 시간을 가지게 됩니다.
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
			// 나갈려고 하는데 플레이어가 CCTV를 보고 있다?
			// 움직이는 데 무조건 실패하고 0.8 ~ 16.7초 동안의 프리징 시간을 가지게 됩니다.
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
	// 이미 폭시는 파이럿 코브를 떠난 상태로,
	// 이 이후로부터 CCTV를 보는 것은 의미가 없습니다.
	// 다만 이 직후 WESTHALLA CCTV 를 보면 폭시가 뛰어오는 애니메이션을 재생합니다.

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