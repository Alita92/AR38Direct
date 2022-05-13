#include "PreCompile.h"
#include "AIChica.h"
#include <GameEngineBase/GameEngineRandom.h>

AIChica::AIChica() // default constructer 디폴트 생성자
	: AILevel_(0)
	, deltatime_(0.0f)
	, curLocation_(LOCATION::SHOWSTAGE)
	, prevLocation_(LOCATION::MAX)
	, state_(this)
	, isDoorLocked_(false)
	, isPlayerStares_(true)
	, isRecentlyMoved_(false)
	, soundDice_(0)
{

}

AIChica::~AIChica() // default destructer 디폴트 소멸자
{

}


void AIChica::InitState()
{
	state_.CreateState("ShowStage", &AIChica::startShowStage, &AIChica::updateShowStage);
	state_.CreateState("RestRooms", &AIChica::startRestRooms, &AIChica::updateRestRooms);
	state_.CreateState("DiningArea", &AIChica::startDiningArea, &AIChica::updateDiningArea);
	state_.CreateState("Kitchen", &AIChica::startKitchen, &AIChica::updateKitchen);
	state_.CreateState("EastHallA", &AIChica::startEastHallA, &AIChica::updateEastHallA);
	state_.CreateState("EastHallB", &AIChica::startEastHallB, &AIChica::updateEastHallB);
	state_.CreateState("OfficeDoor", &AIChica::startROfficeDoor, &AIChica::updateROfficeDoor);
	state_.CreateState("Office", &AIChica::startOffice, &AIChica::updateOffice);

	state_.ChangeState("ShowStage");
}

void AIChica::Reloading()
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SHOWSTAGE;
	prevLocation_ = LOCATION::MAX;
	isDoorLocked_ = false;
	isPlayerStares_ = true;
	isRecentlyMoved_ = false;
	soundDice_ = 0;
	state_.ChangeState("ShowStage");
}

void AIChica::Start()
{
	InitState();

}

void AIChica::Update(float _DeltaTime)
{
	state_.Update();

}

void AIChica::SetAILevel(int _level)
{
	AILevel_ = _level;
	return;
}

void AIChica::AddAILevel(int _level)
{
	AILevel_ += _level;
	return;
}

StateInfo AIChica::startShowStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SHOWSTAGE;
	return StateInfo();
}

StateInfo AIChica::updateShowStage(StateInfo _state)
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
			isRecentlyMoved_ = true;
			return "DiningArea";
		}
	}

	return StateInfo();
}

StateInfo AIChica::startDiningArea(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::DININGAREA;

	return StateInfo();
}

StateInfo AIChica::updateDiningArea(StateInfo _state)
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
				isRecentlyMoved_ = true;
				return "RestRooms";
			}
			break;
			case 1:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
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

StateInfo AIChica::startRestRooms(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::RESTROOMS;

	return StateInfo();
}

StateInfo AIChica::updateRestRooms(StateInfo _state)
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
				isRecentlyMoved_ = true;
				return "Kitchen";
			}
			break;
			case 1:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "EastHallA";
			}
			break;
			case 2:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "DiningArea";
			}
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIChica::startKitchen(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::KITCHEN;
	soundDice_ = randomGenerator_.RandomInt(0, 3);
	return StateInfo();
}

StateInfo AIChica::updateKitchen(StateInfo _state)
{
	if (false == isPlayerStares_)
	{
		moveSound_.GetChannel()->setVolume(0.5);
	}

	switch (soundDice_)
	{
	case 0:
		moveSound_.PlayAlone("ChicaKitchen0.wav", -1);
		break;
	case 1:
		moveSound_.PlayAlone("ChicaKitchen1.wav", -1);
		break;
	case 2:
		moveSound_.PlayAlone("ChicaKitchen2.wav", -1);
		break;
	case 3:
		moveSound_.PlayAlone("ChicaKitchen3.wav", -1);
		break;
	default:
		break;
	}


	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			moveSound_.Stop();
			switch (randomGenerator_.RandomInt(0, 2))
			{
			case 0:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "DiningArea";
			}
			break;
			case 1:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "EastHallA";
			}
			break;
			case 2:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "RestRooms";
			}
			default:
				break;
			}
		}
	}

	return StateInfo();
}

StateInfo AIChica::startEastHallA(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::EASTHALLA;

	return StateInfo();
}

StateInfo AIChica::updateEastHallA(StateInfo _state)
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
				isRecentlyMoved_ = true;
				return "DiningArea";
			}
			break;
			case 1:
			case 2:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "EastHallB";
			}
			break;
			case 3:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "RestRooms";
			}
			break;
			case 4:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
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

StateInfo AIChica::startEastHallB(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::EASTHALLB;

	return StateInfo();
}

StateInfo AIChica::updateEastHallB(StateInfo _state)
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
				isRecentlyMoved_ = true;
				moveSound_.PlayAlone("BonnieChicaMove.wav");
				return "OfficeDoor";
			}
			break;
			case 2:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "EastHallA";
			}
			break;
			case 3:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
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

StateInfo AIChica::startROfficeDoor(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::ROFFICEDOOR;

	return StateInfo();
}

StateInfo AIChica::updateROfficeDoor(StateInfo _state)
{
	if (true == isPlayerStares_)
	{
		return StateInfo();
	}

	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();

	// 문이 열려있다면 CCTV를 보는 중에는 무조건 오피스로 들어오고
	// 문이 닫혀있다면 오피스 제외 움직입니다.
	if (AILevel_ != 0 && deltatime_ >= ACTION_FREQUENCY)
	{
		deltatime_ = 0.0f;

		if (true == randomGenerator_.RandomBool(AILevel_ / 20.0f))
		{
			if (false == isDoorLocked_ && false == isPlayerStares_)
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				return "Office";
			}
			else if (false == isDoorLocked_ && true == isPlayerStares_)
			{
				return StateInfo();
			}

			switch (randomGenerator_.RandomInt(0, 3))
			{
			case 0:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				moveSound_.PlayAlone("BonnieChicaMove.wav");
				return "EastHallB";
			}
			break;
			case 1:
			case 2:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				moveSound_.PlayAlone("BonnieChicaMove.wav");
				return "EastHallA";
			}
			break;
			case 3:
			{
				prevLocation_ = curLocation_;
				isRecentlyMoved_ = true;
				moveSound_.PlayAlone("BonnieChicaMove.wav");
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

StateInfo AIChica::startOffice(StateInfo _state)
{
	curLocation_ = LOCATION::OFFICE;

	return StateInfo();
}

StateInfo AIChica::updateOffice(StateInfo _state)
{

	return StateInfo();
}

void AIChica::ActivateJumpscare()
{
	if (true == state_.IsCurStateName("Office"))
	{
		return;
	}

	state_.ChangeState("Office");
}

void AIChica::ActivateAction()
{
	deltatime_ = ACTION_FREQUENCY;
}