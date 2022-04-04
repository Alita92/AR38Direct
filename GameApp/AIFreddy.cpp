#include "PreCompile.h"
#include "AIFreddy.h"

// 프레디는 무조건, 보니와 치카가 쇼 스테이지를 비운 후부터 움직이기 시작해야 한다.
// 프레디는 한 번 움직이면 다시 뒤로 돌아가지 않는다 - 물론 문 앞까지 와서 공격에 실패하면 뒤로 돌아가긴 하나, 
// 그것은 플레이어를 공격하기 위해 시스템상 그렇게 되어있는 것 뿐이다. 자세히 말하자면, 공격을 한 번 더 시도하는 것이다.

AIFreddy::AIFreddy() // default constructer 디폴트 생성자
	:AILevel_(0), deltatime_(0.0f), curLocation_(LOCATION::SHOWSTAGE), prevLocation_(LOCATION::SHOWSTAGE), state_(this), isDoorLocked_(false), isPlayerStares_(true)
{

}

AIFreddy::~AIFreddy() // default destructer 디폴트 소멸자
{

}

void AIFreddy::InitState()
{
	state_.CreateState("ShowStage", &AIFreddy::startShowStage, &AIFreddy::updateShowStage);
	state_.CreateState("RestRooms", &AIFreddy::startRestRooms, &AIFreddy::updateRestRooms);
	state_.CreateState("DiningArea", &AIFreddy::startDiningArea, &AIFreddy::updateDiningArea);
	state_.CreateState("EastHallA", &AIFreddy::startEastHallA, &AIFreddy::updateEastHallA);
	state_.CreateState("EastHallB", &AIFreddy::startEastHallB, &AIFreddy::updateEastHallB);
	state_.CreateState("Office", &AIFreddy::startOffice, &AIFreddy::updateOffice);

	state_.ChangeState("ShowStage");
}

void AIFreddy::Start()
{
	InitState();

}

void AIFreddy::Update(float _DeltaTime)
{
	state_.Update();

}

void AIFreddy::SetAILevel(int _level)
{
	AILevel_ = _level;
	return;
}

void AIFreddy::AddAILevel(int _level)
{
	AILevel_ += _level;
	return;
}

StateInfo AIFreddy::startShowStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SHOWSTAGE;
	return StateInfo();
}

StateInfo AIFreddy::updateShowStage(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			// 주사위를 굴려 "이동" 이 나온 상태입니다.
			// 다만 쇼 스테이지에서 이동 가능한 구간은 DiningArea 밖에 없는 관계로...
			// 이 이후로 쇼 스테이지로 다시 갈 일은 없습니다.
			prevLocation_ = curLocation_;
			return "DiningArea";
		}
	}

	return StateInfo();
}

StateInfo AIFreddy::startDiningArea(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::DININGAREA;

	return StateInfo();
}

StateInfo AIFreddy::updateDiningArea(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 1))
			{
			case 0:
			{
				prevLocation_ = curLocation_;
				return "RestRooms";
			}
			break;
			case 1:
			{
				prevLocation_ = curLocation_;
				return "EastHallA";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIFreddy::startRestRooms(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::RESTROOMS;

	return StateInfo();
}

StateInfo AIFreddy::updateRestRooms(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 2))
			{
			case 0:
			{
				prevLocation_ = curLocation_;
				return "Kitchen";
			}
			break;
			case 1:
			{
				prevLocation_ = curLocation_;
				return "EastHallA";
			}
			break;
			case 2:
			{
				prevLocation_ = curLocation_;
				return "DiningArea";
			}
			default:
				break;
			}
		}
	}

	return StateInfo();
}


StateInfo AIFreddy::startEastHallA(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::EASTHALLA;

	return StateInfo();
}

StateInfo AIFreddy::updateEastHallA(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 4))
			{
			case 0:
			{
				prevLocation_ = curLocation_;
				return "DiningArea";
			}
			break;
			case 1:
			case 2:
			{
				prevLocation_ = curLocation_;
				return "EastHallB";
			}
			break;
			case 3:
			{
				prevLocation_ = curLocation_;
				return "RestRooms";
			}
			break;
			case 4:
			{
				prevLocation_ = curLocation_;
				return "Kitchen";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIFreddy::startEastHallB(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::EASTHALLB;

	return StateInfo();
}

StateInfo AIFreddy::updateEastHallB(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 3))
			{
			case 0:
			case 1:
			{
				prevLocation_ = curLocation_;
				return "OfficeDoor";
			}
			break;
			case 2:
			{
				prevLocation_ = curLocation_;
				return "EastHallA";
			}
			break;
			case 3:
			{
				prevLocation_ = curLocation_;
				return "Kitchen";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIFreddy::startOffice(StateInfo _state)
{
	curLocation_ = LOCATION::OFFICE;

	return StateInfo();
}

StateInfo AIFreddy::updateOffice(StateInfo _state)
{

	return StateInfo();
}