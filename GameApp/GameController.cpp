#include "PreCompile.h"
#include "GameController.h"

// Enemy AI
#include "AIBonnie.h"

GameController::GameController() // default constructer ����Ʈ ������
	: CurViewState_(LOCATION::OFFICE), CurCCTVState_(LOCATION::SHOWSTAGE), elecUsageTimer_(0.0f), state_(this), curElecUsage_(0), curElectricity_(0.0f), isElecCheckOff_(false)
	, aiBonnie_(nullptr), aiChica_(nullptr), aiFoxy_(nullptr), aiFreddy_(nullptr)
	, curTime_(0), timeUsageTimer_(0.0f), isTimeCheckOff_(false)
	, curDay_(0)
	, lDoorClosed_(false), lDoorLighted_(false), rDoorClosed_(false), rdoorLighted_(false)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}


void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);
	state_.CreateState("NoElec", &GameController::startNoelec, &GameController::updateNoelec);
	state_.CreateState("Win", &GameController::startWin, &GameController::updateWin);

	state_.ChangeState("Idle");
}

void GameController::InitPlayStatus()
{
	CurViewState_ = LOCATION::OFFICE;
	CurCCTVState_ = LOCATION::SHOWSTAGE;
	curElecUsage_ = 1;
	curElectricity_ = MAX_ELECTRICITIY_RATE;
	curTime_ = 0;
	curDay_ = 1;
}

void GameController::InitEnemy()
{
	aiBonnie_ = GetLevel()->CreateActor<AIBonnie>();
//	aiChica_ = GetLevel()->CreateActor<AIChica>();
//	aiFoxy_ = GetLevel()->CreateActor<AIFoxy>();
//	aiFreddy_ = GetLevel()->CreateActor<AIFreddy>();
}

void GameController::InitInput()
{
#ifdef _DEBUG
	// ����� ���� ��ǲ
	GameEngineInput::GetInst().CreateKey("Debug_Q", 'Q');
	GameEngineInput::GetInst().CreateKey("Debug_W", 'W');
	GameEngineInput::GetInst().CreateKey("Debug_E", 'E');
	GameEngineInput::GetInst().CreateKey("Debug_A", 'A');
	GameEngineInput::GetInst().CreateKey("Debug_S", 'S');
	GameEngineInput::GetInst().CreateKey("Debug_D", 'D');
#endif


}


void GameController::Start()
{
	InitState();
	InitPlayStatus();
	InitEnemy();
}

void GameController::CheckElectricityUsage()
{
	// �ǽð� ��ŸŸ���� ������ ������ �Ҹ��ŵ�ϴ�.
	// ������ 0�� �Ǹ� ��Ʈ�ѷ��� ������Ʈ�� ������ ��ȯ��ŵ�ϴ�.
	if (true == isElecCheckOff_ || curElectricity_ < 0.0f)
	{
		return;
	}
	// ������ (9.6 / ��뷮)�ʸ��� 1%�� �Ҹ�ȴ� (�ƹ��͵� �� �� �� ��뷮 1)
	// �� �� 2�Ϲ� ���ʹ� ���������� �߰� ���� �Ҹ� ����
	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curElecUsage_ <= elecUsageTimer_)
	{
		elecUsageTimer_ = 0.0f;
		curElectricity_ -= 1.0f;
	}
		// 2�Ϲ� 9 %
		// 3�Ϲ� 10.8 %
		// 4�Ϲ� 13.5 %
		// 5�Ϲ�~18 %
	return;
}

void GameController::CheckTime()
{
	// �ǽð� ��ŸŸ���� ������ ���� �� �ð��� ������ �մϴ�.
	// 6�÷� ��Ŀ�� ���� �� ���� �¸� ������ �����ϴ�.
	if (true == isTimeCheckOff_ || 6 == curTime_)
	{
		return;
	}

	timeUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (EACH_HOUR_REAL_DURATION <= timeUsageTimer_)
	{
		// 89�ʰ� ������ �ð� ��Ŀ�� 1�ð��� �����ݴϴ�.
		timeUsageTimer_ = 0.0f;
		curTime_ += 1;

		if (6 < curTime_)
		{
			GameEngineDebug::MsgBoxError("�ð��� 7�� �̻��ӿ��� ������ ������ �ʽ��ϴ�.");
		}

		return;
	}

	return;
}

void GameController::Update(float _Deltatime)
{
	state_.Update();
	CheckTime();
	CheckElectricityUsage();
}

StateInfo GameController::startIdle(StateInfo _state)
{
	CurViewState_ = LOCATION::NONE;

	return StateInfo();
}

StateInfo GameController::updateIdle(StateInfo _state)
{
	if (curTime_ == 6)
	{
		return "Win";
	}

	if (curElectricity_ < 0)
	{
		return "Noelec";
	}

	return StateInfo();
}

StateInfo GameController::startCCTV(StateInfo _state)
{
	// CCTV�� �۵���Ų �����Դϴ�.
	// ���� �Ҹ��� 1���� ����ϸ�,
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{
	if (curTime_ == 6 || curElectricity_ < 0)
	{
		// �ð�, ���� �ϳ��� ���� ���� �� ������ CCTV ��尡 �����˴ϴ�.
		// ���Ĵ� Idle ���� ó�����ݴϴ�.
		return "Idle";
	}

	switch (CurCCTVState_)
	{
		// �� CCTV�� ��� �����ߴ����� ����
		// ȭ���� �ٲ� �����ݴϴ�.
	case LOCATION::OFFICE:
		break;
	case LOCATION::LOFFICEDOOR:
		break;
	case LOCATION::ROFFICEDOOR:
		break;
	case LOCATION::SHOWSTAGE:
		break;
	case LOCATION::KITCHEN:
		break;
	case LOCATION::BACKSTAGE:
		break;
	case LOCATION::DININGAREA:
		break;
	case LOCATION::PIRATECOVE:
		break;
	case LOCATION::EASTHALLA:
		break;
	case LOCATION::EASTHALLB:
		break;
	case LOCATION::WESTHALLA:
		break;
	case LOCATION::WESTHALLB:
		break;
	case LOCATION::RESTROOMS:
		break;
	case LOCATION::SUPPLYCLOSET:
		break;
	case LOCATION::NONE:
		break;
	case LOCATION::MAX:
		break;
	default:
		break;
	}

	return StateInfo();
}

StateInfo GameController::startNoelec(StateInfo _state)
{
	isElecCheckOff_ = true;
	isTimeCheckOff_ = true;
	timeUsageTimer_ = 0.0f;
	elecUsageTimer_ = 0.0f;
	return StateInfo();
}

StateInfo GameController::updateNoelec(StateInfo _state)
{

// 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ���߰� ȭ���� �����ȴ�
// ���� 2�ʸ��� 1 / 5 Ȯ���� ������ �������ɾ�

	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (5.0f <= elecUsageTimer_)
	{	// ������ ���� ���� 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ����Ǳ� �����ϰ�
		elecUsageTimer_ = 0.0f;

		
	}

	return StateInfo();
}

StateInfo GameController::startWin(StateInfo _state)
{
	return StateInfo();
}

StateInfo GameController::updateWin(StateInfo _state)
{
	return StateInfo();
}