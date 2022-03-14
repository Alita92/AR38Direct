#include "PreCompile.h"
#include "AIBonnie.h"

AIBonnie::AIBonnie() // default constructer 디폴트 생성자
	:AILevel_(0.0f), actionFrequency_(0.0f), deltatime_(0.0f), curLocation_(LOCATION::MAX), nextLocation_(LOCATION::MAX), state_(this)
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

StateInfo AIBonnie::startShowStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SHOWSTAGE;
}

StateInfo AIBonnie::updateShowStage(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();


}

StateInfo AIBonnie::startBackStage(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::BACKSTAGE;
}

StateInfo AIBonnie::updateBackStage(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}
StateInfo AIBonnie::startDiningArea(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::DININGAREA;
}
StateInfo AIBonnie::updateDiningArea(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}

StateInfo AIBonnie::startWestHallA(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::WESTHALLA;
}
StateInfo AIBonnie::updateWestHallA(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}

StateInfo AIBonnie::startWestHallB(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::WESTHALLB;
}
StateInfo AIBonnie::updateWestHallB(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}

StateInfo AIBonnie::startSupplyCloset(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::SUPPLYCLOSET;
}
StateInfo AIBonnie::updateSupplyCloset(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}

StateInfo AIBonnie::startOfficeDoor(StateInfo _state)
{
	deltatime_ = 0.0f;
	curLocation_ = LOCATION::LOFFICEDOOR;
}
StateInfo AIBonnie::updateOfficeDoor(StateInfo _state)
{
	deltatime_ += GameEngineTime::GetInst().GetDeltaTime();
}

StateInfo AIBonnie::startOffice(StateInfo _state)
{
	curLocation_ = LOCATION::OFFICE;
}
StateInfo AIBonnie::updateOffice(StateInfo _state)
{

}
