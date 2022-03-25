#include "PreCompile.h"
#include "GameController.h"
#include <GameEngine/GameEngineImageRenderer.h>


// Enemy AI
#include "AIBonnie.h"

GameController::GameController() // default constructer ����Ʈ ������
	: CurViewState_(LOCATION::OFFICE), CurCCTVState_(LOCATION::SHOWSTAGE), elecUsageTimer_(0.0f), state_(this), curElecUsage_(0), curElectricity_(0.0f), isElecCheckOff_(false)
	, aiBonnie_(nullptr), aiChica_(nullptr), aiFoxy_(nullptr), aiFreddy_(nullptr)
	, curTime_(0), timeUsageTimer_(0.0f), isTimeCheckOff_(false)
	, curDay_(0)
	, isLdoorClosed_(false), lDoorLighted_(false), isRdoorClosed_(false), rdoorLighted_(false)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}


void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);

	state_.CreateState("CCTVOpen", &GameController::startCCTVOpen, &GameController::updateCCTVOpen);
	state_.CreateState("CCTVClose", &GameController::startCCTVClose, &GameController::updateCCTVClose);

	state_.CreateState("CCTV", &GameController::startCCTV, &GameController::updateCCTV);
	
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

void GameController::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::BACKGROUND0)});
		mainRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
	}

	{
		fanRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		fanRenderer_->SetImage("OfficeFanDefault.png", true);
		fanRenderer_->GetTransform()->SetLocalPosition({ 49.0f, -41.0f, static_cast<float>(RenderOrder::OBJECT1) });
		fanRenderer_->CreateAnimation("OfficeFan.png", "OfficeFan", 0, 2, 0.02f);
		fanRenderer_->SetChangeAnimation("OfficeFan");
	}

	{
		lDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		lDoorRenderer_->SetImage("LdoorStatic.png", true);
		lDoorRenderer_->GetTransform()->SetLocalPosition({ -550.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1)});
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorClose", 14, 0, 0.04f, false);
		lDoorRenderer_->CreateAnimation("LdoorAnimation.png", "LdoorOpen", 0, 14, 0.04f, false);
	}

	{
		rDoorRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		rDoorRenderer_->SetImage("RdoorStatic.png", true);
		rDoorRenderer_->GetTransform()->SetLocalPosition({ 550.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT1) });
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorClose", 14, 0, 0.04f, false);
		rDoorRenderer_->CreateAnimation("RdoorAnimation.png", "RdoorOpen", 0, 14, 0.04f, false);
	}

	{		
		CCTVRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVRenderer_->SetImage("ShowStage_Default.png", true);
		CCTVRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT0) });
		CCTVRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVOpen", 0, 9, 0.04f, false);
		CCTVRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVClose", 9, 0, 0.04f, false);
		CCTVRenderer_->Off();
	}
}

void GameController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f ,0.0f, 10.0f });
	InitState();
	InitAnimation();
	InitPlayStatus();
	InitEnemy();

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P');
	}

	
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

	if (true == GameEngineInput::GetInst().Down("DEBUG_SKIPSCENE"))
	{
		// �������ɾ� ����� ��
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f,0.0f, -50.0f });
		mainRenderer_->SetChangeAnimation("JumpScareBonnie");
		// ���� �ִϸ��̼��� ������� �������� ������� ����..
	}


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

	if (true == GameEngineInput::GetInst().Down("LDoor_Toggle"))
	{
		if (false == isLdoorClosed_)
		{
			lDoorRenderer_->SetChangeAnimation("LdoorClose");
			isLdoorClosed_ = true;
		}
		else
		{

			lDoorRenderer_->SetChangeAnimation("LdoorOpen");
			isLdoorClosed_ = false;
		}
	}

	if (true == GameEngineInput::GetInst().Down("RDoor_Toggle"))
	{
		if (false == isRdoorClosed_)
		{
			rDoorRenderer_->SetChangeAnimation("RdoorClose");
			isRdoorClosed_ = true;
		}
		else
		{
			rDoorRenderer_->SetChangeAnimation("RdoorOpen");
			isRdoorClosed_ = false;
		}
	}

	if (true == GameEngineInput::GetInst().Down("CCTV_Toggle"))
	{
		return "CCTVOpen";
	}

	return StateInfo();
}

StateInfo GameController::startCCTVOpen(StateInfo _state)
{
	// CCTV �۵� �ִϸ��̼ǿ� �ռ� ���� ������ ���� �����մϴ�.
	CCTVRenderer_->On();
	CCTVRenderer_->SetChangeAnimation("CCTVOpen");
	return StateInfo();
}

StateInfo GameController::updateCCTVOpen(StateInfo _state)
{
	// CCTV �۵� �ִϸ��̼��� ���⼭ �۵� ��ŵ�ϴ�.
	// �۵��� ª�� �ð������� � ��ǲ�� ������ �ʵ��� �����մϴ�.


	if (true == CCTVRenderer_->IsCurAnimationEnd())
	{
		return "CCTV";
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
	{
		CCTVRenderer_->SetImage("ShowStage_Default.png", true);
	}
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

	if (true == GameEngineInput::GetInst().Down("CCTV_Toggle"))
	{
		return "CCTVClose";
	}

	return StateInfo();
}


StateInfo GameController::startCCTVClose(StateInfo _state)
{
	CCTVRenderer_->Off();
	return StateInfo();
}

StateInfo GameController::updateCCTVClose(StateInfo _state)
{
	mainRenderer_->SetImage("OfficeBasic.png", true);
	return "Idle";
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

