#include "PreCompile.h"
#include "AIBonnie.h"
#include <GameEngineBase/GameEngineRandom.h>

AIBonnie::AIBonnie() // default constructer 디폴트 생성자
	:AILevel_(0), deltatime_(0.0f), curLocation_(LOCATION::MAX), nextLocation_(LOCATION::MAX), state_(this), isDoorLocked_(false)
{

}

AIBonnie::~AIBonnie() // default destructer 디폴트 소멸자
{

}

/*
보니는 이동 경로를 건너 뛸 수 있습니다.
*/

void AIBonnie::InitState()
{
	state_.CreateState("ShowStage", &AIBonnie::startShowStage, &AIBonnie::updateShowStage);
	state_.CreateState("BackStage", &AIBonnie::startBackStage, &AIBonnie::updateBackStage);
	state_.CreateState("DiningArea", &AIBonnie::startDiningArea, &AIBonnie::updateDiningArea);
	state_.CreateState("WestHallA", &AIBonnie::startWestHallA, &AIBonnie::updateWestHallA);
	state_.CreateState("WestHallB", &AIBonnie::startWestHallB, &AIBonnie::updateWestHallB);
	state_.CreateState("SupplyCloset", &AIBonnie::startSupplyCloset, &AIBonnie::updateSupplyCloset);
	state_.CreateState("OfficeDoor", &AIBonnie::startLOfficeDoor, &AIBonnie::updateLOfficeDoor);
	state_.CreateState("Office", &AIBonnie::startOffice, &AIBonnie::updateOffice);

	state_.ChangeState("ShowStage");
}

void AIBonnie::Start()
{
	InitState();

}

void AIBonnie::Update(float _DeltaTime)
{
	state_.Update();

}

void AIBonnie::SetAILevel(int _level)
{
	AILevel_ = _level;
	return;
}

void AIBonnie::AddAILevel(int _level)
{
	AILevel_ += _level;
	return;
}

StateInfo AIBonnie::startShowStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SHOWSTAGE;
	return StateInfo();
}

StateInfo AIBonnie::updateShowStage(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_/20.0f))
		{
			// 주사위를 굴려 "이동" 이 나온 상태입니다.
			// 다만 쇼 스테이지에서 이동 가능한 구간은 DiningArea 밖에 없는 관계로...
			// 이 이후로 쇼 스테이지로 다시 갈 일은 없습니다.

			return "DiningArea";
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startBackStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::BACKSTAGE;

	return StateInfo();
}

StateInfo AIBonnie::updateBackStage(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 1))
			{
			case 0: // 식당
			{
				return "DiningArea";
			}
			break;
			case 1: // 서쪽 홀 A
			{
				return "WestHallA";
			}
			break;

			default:
				break;
			}
		}
	}

	return StateInfo();
}
StateInfo AIBonnie::startDiningArea(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::DININGAREA;

	return StateInfo();
}

StateInfo AIBonnie::updateDiningArea(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 2))
			{
			case 0: // 백스테이지
			{
				return "BackStage";
			}
			break;
			case 1: // 서쪽 홀 A
			{
				return "WestHallA";
			}
			break;
			case 2: // 물품 보관실
			{
				return "SupplyCloset";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startWestHallA(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::WESTHALLA;

	return StateInfo();
}

StateInfo AIBonnie::updateWestHallA(StateInfo _state)
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
				return "DiningArea";
			}
			break;
			case 1:
			{
				return "WestHallB";
			}
			break;
			case 2:
			{
				return "SupplyCloset";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startWestHallB(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::WESTHALLB;

	return StateInfo();
}

StateInfo AIBonnie::updateWestHallB(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 5))
			{
			case 0:
			case 1:
			case 2:
			{
				return "OfficeDoor";
			}
			break;
			case 3:
			{
				return "WestHallA";
			}
			break;
			case 4:
			{
				return "SupplyCloset";
			}
			break;
			case 5:
			{
				return "DiningArea";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startSupplyCloset(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SUPPLYCLOSET;

	return StateInfo();
}
StateInfo AIBonnie::updateSupplyCloset(StateInfo _state)
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
				return "DiningArea";
			}
			break;
			case 1:
			{
				return "WestHallB";
			}
			break;
			case 2:
			{
				return "WestHallA";
			}
			break;
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startLOfficeDoor(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::LOFFICEDOOR;

	return StateInfo();
}
StateInfo AIBonnie::updateLOfficeDoor(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();


	// 문이 열려있다면 CCTV를 보는 중에는 무조건 오피스로 들어오고
	// 문이 닫혀있다면 오피스 제외 움직입니다.
	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			switch (randomGenerator_.RandomInt(0, 5))
			{
			case 0:
			case 1:
			case 2:
			{
				if (false == isDoorLocked_)
				{
					return "Office";
				}

				switch (randomGenerator_.RandomInt(0, 2))
				{
				case 0:
				{
					return "WestHallB";
				}
					break;
				case 1:
				{
					return "WestHallA";
				}
					break;
				case 2:
				{
					return "DiningArea";
				}
					break;

				default:
					break;
				}
			}
			break;
			case 3:
			{
				return "WestHallB";
			}
			break;
			case 4:
			{
				return "WestHallA";
			}
			break;
			case 5:
			{
				return "DiningArea";
			}
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIBonnie::startOffice(StateInfo _state)
{
	curLocation_ = LOCATION::OFFICE;

	return StateInfo();
}
StateInfo AIBonnie::updateOffice(StateInfo _state)
{
	

	return StateInfo();
}
