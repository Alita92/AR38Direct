#include "PreCompile.h"
#include "GameController.h"
#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// UIController
#include "UIController.h"

// Enemy AI
#include "AIBonnie.h"

GameController::GameController() // default constructer ����Ʈ ������
	: CurPlayerState_(PLAYERSTATUS::OFFICE), CurCCTVState_(LOCATION::SHOWSTAGE), elecUsageTimer_(0.0f), state_(this), curPowerLevel_(0), curPowerRate_(0.0f), isElecCheckOff_(false)
	, aiBonnie_(nullptr), aiChica_(nullptr), aiFoxy_(nullptr), aiFreddy_(nullptr)
	, curTime_(0), timeUsageTimer_(0.0f), isTimeCheckOff_(false)
	, curDay_(0)
	, isLdoorClosed_(false), lDoorLighted_(false), isRdoorClosed_(false), rdoorLighted_(false)
	, noElecDeltaTime_(0.0f), noElecTimerCounter_(0)
{

}

GameController::~GameController() // default destructer ����Ʈ �Ҹ���
{

}

void GameController::InitUIController()
{
	UIController_ = GetLevel()->CreateActor<UIController>();
}

void GameController::InitState()
{
	state_.CreateState("Idle", &GameController::startIdle, &GameController::updateIdle);

	state_.CreateState("CCTVOpen", &GameController::startCCTVOpen, &GameController::updateCCTVOpen);
	state_.CreateState("CCTVClose", &GameController::startCCTVClose, &GameController::updateCCTVClose);

	state_.CreateState("CCTV", &GameController::startCCTV, &GameController::updateCCTV);
	
	state_.CreateState("NoElec", &GameController::startNoElec, &GameController::updateNoElec);
	state_.CreateState("HeisComing", &GameController::startHeisComing, &GameController::updateHeisComing);
	state_.CreateState("HeKillsYou", &GameController::startHeKillsYou, &GameController::updateHeKillsYou);
	state_.CreateState("NoElecDeath", &GameController::startNoElecDeath, &GameController::updateNoElecDeath);

	state_.CreateState("Win", &GameController::startWin, &GameController::updateWin);

	state_.ChangeState("Idle");
}

void GameController::InitPlayStatus()
{
	CurPlayerState_ = PLAYERSTATUS::OFFICE;
	CurCCTVState_ = LOCATION::SHOWSTAGE;
	curPowerLevel_ = 1;
	curPowerRate_ = MAX_ELECTRICITIY_RATE;
	curTime_ = 0;
	curDay_ = 1;
}

void GameController::InitEnemy()
{
	aiBonnie_ = GetLevel()->CreateActor<AIBonnie>();
	aiBonnie_->SetAILevel(15);
//	aiChica_ = GetLevel()->CreateActor<AIChica>();
//	aiFoxy_ = GetLevel()->CreateActor<AIFoxy>();
//	aiFreddy_ = GetLevel()->CreateActor<AIFreddy>();
}

void GameController::InitAnimation()
{
	{
		mainRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		mainRenderer_->SetImage("OfficeBasic.png", true);
		mainRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::BACKGROUND1)});
		mainRenderer_->CreateAnimation("JumpScareBonnie.png", "JumpScareBonnie", 0, 10, 0.04f, true);
		mainRenderer_->CreateAnimationFolder("NoElec", "NoElec", 0.04f, true);
		mainRenderer_->CreateAnimationFolder("NoElecBlink", "NoElecBlink", 0.04f, false);
		mainRenderer_->CreateAnimationFolder("NoElecFreddy", "NoElecFreddy", 0.04f, false);
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
		CCTVAnimationRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVAnimationRenderer_->SetImage("ShowStage_Default.png", true);
		CCTVAnimationRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::OBJECT0) });
		CCTVAnimationRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVOpen", 0, 9, 0.04f, false);
		CCTVAnimationRenderer_->CreateAnimation("CCTVAnimation.png", "CCTVClose", 9, 0, 0.04f, false);
		CCTVAnimationRenderer_->Off();
	}

	{
		CCTVRealRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		CCTVRealRenderer_->SetImage("ShowStage_Default.png", true);
		CCTVRealRenderer_->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, static_cast<float>(RenderOrder::CCTV) });
		CCTVRealRenderer_->Off();
	}
}

void GameController::Start()
{
	GetTransform()->SetWorldPosition({ 0.0f ,0.0f, 10.0f });
	InitUIController();
	InitState();
	InitAnimation();
	InitPlayStatus();
	InitEnemy();

	if (false == GameEngineInput::GetInst().IsKey("DEBUG_SKIPSCENE"))
	{
		GameEngineInput::GetInst().CreateKey("DEBUG_SKIPSCENE", 'P');
	}
	
}



void GameController::CheckTime()
{
	// �ǽð� ��ŸŸ���� ������ ���� �� �ð��� ������ �մϴ�.
	// 6�÷� ��Ŀ�� ���� �� ���� �¸� ������ �����ϴ�.
	if (6 == curTime_)
	{
		return;
	}

	timeUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (EACH_HOUR_REAL_DURATION <= timeUsageTimer_)
	{
		// 89�ʰ� ������ �ð� ��Ŀ�� 1�ð��� �����ݴϴ�.
		timeUsageTimer_ = 0.0f;
		curTime_ += 1;
		UIController_->SetTimeRenderer(curTime_);

		if (6 < curTime_)
		{
			GameEngineDebug::MsgBoxError("�ð��� 7�� �̻��ӿ��� ������ ������ �ʽ��ϴ�.");
		}

		return;
	}

	return;
}

void GameController::CheckElectricityUsage()
{
	// �ǽð� ��ŸŸ���� ������ ������ �Ҹ��ŵ�ϴ�.
	// ������ 0�� �Ǹ� ��Ʈ�ѷ��� ������Ʈ�� ������ ��ȯ��ŵ�ϴ�.


	if (true == isElecCheckOff_ || curPowerRate_ <= 0.0f)
	{
		return;
	}
	// ������ (9.6 / ��뷮)�ʸ��� 1%�� �Ҹ�ȴ� (�ƹ��͵� �� �� �� ��뷮 1)
	// �� �� 2�Ϲ� ���ʹ� ���������� �߰� ���� �Ҹ� ����
	elecUsageTimer_ += GameEngineTime::GetInst().GetDeltaTime();

	if (ELECTRICITY_DEFAULT_USAGE / curPowerLevel_ <= elecUsageTimer_)
	{
		elecUsageTimer_ = 0.0f;
		curPowerRate_ -= 1.0f;
		UIController_->SetPowerRateRenderer(curPowerRate_);
	}
	// 2�Ϲ� 9 %
	// 3�Ϲ� 10.8 %
	// 4�Ϲ� 13.5 %
	// 5�Ϲ�~18 %
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
	CurPlayerState_ = PLAYERSTATUS::OFFICE;
	return StateInfo();
}

StateInfo GameController::updateIdle(StateInfo _state)
{
	if (curTime_ == 6)
	{
		return "Win";
	}

	if (curPowerRate_ <= 0.0f)
	{
		return "NoElec";
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

	UIController_->CCTVButtonCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCCTVButton, this, std::placeholders::_1));


	return StateInfo();
}

StateInfo GameController::startCCTVOpen(StateInfo _state)
{
	// CCTV �۵� �ִϸ��̼ǿ� �ռ� ���� ������ ���� �����մϴ�.
	CCTVAnimationRenderer_->On();
	CCTVAnimationRenderer_->SetChangeAnimation("CCTVOpen");
	return StateInfo();
}

StateInfo GameController::updateCCTVOpen(StateInfo _state)
{
	// CCTV �۵� �ִϸ��̼��� ���⼭ �۵� ��ŵ�ϴ�.
	// �۵��� ª�� �ð������� � ��ǲ�� ������ �ʵ��� �����մϴ�.


	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		return "CCTV";
	}

	return StateInfo();
}

StateInfo GameController::startCCTV(StateInfo _state)
{
	// CCTV�� �۵���Ų �����Դϴ�.
	// ���� �Ҹ��� 1���� ����ϸ�,
	fanRenderer_->Off();
	CCTVAnimationRenderer_->Off();
	CurPlayerState_ = PLAYERSTATUS::CCTV;
	UIController_->SwitchUIState(PLAYERSTATUS::CCTV);
	return StateInfo();
}

StateInfo GameController::updateCCTV(StateInfo _state)
{


	if (curPowerRate_ <= 0)
	{
		// �ð�, ���� �ϳ��� ���� ���� �� ������ CCTV ��尡 �����˴ϴ�.
		// ���Ĵ� Idle ���� ó�����ݴϴ�.
		//fanRenderer_->Off();
		//mainRenderer_->SetImage("NoElecStatic.png", true);
		//CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
		return "NoElec";
	}

	switch (CurCCTVState_)
	{
		// �� CCTV�� ��� �����ߴ����� ����
		// ȭ���� �ٲ� �����ݴϴ�.
	case LOCATION::SHOWSTAGE:
	{
		CCTVRealRenderer_->On();

		if (LOCATION::SHOWSTAGE != aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("ShowStage_BonnieGone.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("ShowStage_Default.png", true);
	}
		break;
	case LOCATION::KITCHEN:
	{
		CCTVRealRenderer_->On();

		CCTVRealRenderer_->SetImage("Kitchen.png", true);
	}
		break;
	case LOCATION::BACKSTAGE: 
	{
		CCTVRealRenderer_->On();

		if (LOCATION::BACKSTAGE == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("BackStage_Bonnie0.png", true);
			break;
		}


		CCTVRealRenderer_->SetImage("BackStage_Default.png", true);
	}
		break;
	case LOCATION::DININGAREA:
	{
		CCTVRealRenderer_->On();

		if (LOCATION::BACKSTAGE == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("DiningArea_Bonnie0.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("DiningArea_Default.png", true);
	}
		break;
	case LOCATION::PIRATECOVE:
	{
		CCTVRealRenderer_->On();
		CCTVRealRenderer_->SetImage("PirateCove_Lv1.png", true);
	}
		break;
	case LOCATION::EASTHALLA:
	{
		CCTVRealRenderer_->On();
		CCTVRealRenderer_->SetImage("EastHallA_Default.png", true);
	}
		break;
	case LOCATION::EASTHALLB:
	{
		CCTVRealRenderer_->On();
		CCTVRealRenderer_->SetImage("EastHallB_Default.png", true);
	}
		break;
	case LOCATION::WESTHALLA:
	{
		CCTVRealRenderer_->On();

		if (LOCATION::WESTHALLA == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("WestHallA_Bonnie.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("WestHallA_Default.png", true);
	}
		break;
	case LOCATION::WESTHALLB:
	{
		CCTVRealRenderer_->On();

		if (LOCATION::WESTHALLA == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("WestHallB_Bonnie0.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("WestHallB_Default.png", true);
	}
		break;
	case LOCATION::RESTROOMS:
	{
		CCTVRealRenderer_->On();
		CCTVRealRenderer_->SetImage("RestRooms_Default.png", true);
	}
		break;
	case LOCATION::SUPPLYCLOSET:
	{
		CCTVRealRenderer_->On();

		if (LOCATION::SUPPLYCLOSET == aiBonnie_->GetLocation())
		{
			CCTVRealRenderer_->SetImage("SuppltCloset_Bonnie.png", true);
			break;
		}

		CCTVRealRenderer_->SetImage("SupplyCloset_Default.png", true);
	}
		break;
	case LOCATION::NONE:
	{

	}
		break;
	case LOCATION::MAX:
		break;
	default:
		break;
	}


	{
		UIController_->CCTVButtonCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCCTVButton, this, std::placeholders::_1));
		UIController_->cam1ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1A, this, std::placeholders::_1));
		UIController_->cam1BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1B, this, std::placeholders::_1));
		UIController_->cam1CCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam1C, this, std::placeholders::_1));
		UIController_->cam5Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam5, this, std::placeholders::_1));
		UIController_->cam3Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam3, this, std::placeholders::_1));
		UIController_->cam2ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam2A, this, std::placeholders::_1));
		UIController_->cam2BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam2B, this, std::placeholders::_1));
		UIController_->cam7Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam7, this, std::placeholders::_1));
		UIController_->cam6Collision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam6, this, std::placeholders::_1));
		UIController_->cam4ACollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam4A, this, std::placeholders::_1));
		UIController_->cam4BCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(InGameCollisonType::MOUSEPOINTER), std::bind(&GameController::CollisionCam4B, this, std::placeholders::_1));
	}

	return StateInfo();
}


StateInfo GameController::startCCTVClose(StateInfo _state)
{
	CCTVRealRenderer_->Off();
	CCTVAnimationRenderer_->On();

	if (curPowerRate_ != 0.0f)
	{
		fanRenderer_->On();
	}

	CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
	return StateInfo();
}

StateInfo GameController::updateCCTVClose(StateInfo _state)
{
	if (true == CCTVAnimationRenderer_->IsCurAnimationEnd())
	{
		if (curPowerRate_ != 0)
		{
			mainRenderer_->SetImage("OfficeBasic.png", true);

		}

		CCTVAnimationRenderer_->Off();

		return "Idle";
	}
	return StateInfo();
}

StateInfo GameController::startNoElec(StateInfo _state)
{
	UIController_->Off();

	if (CurPlayerState_ != PLAYERSTATUS::OFFICE)
	{
		CCTVAnimationRenderer_->SetChangeAnimation("CCTVClose");
		CCTVRealRenderer_->Off();
	}
	
	isElecCheckOff_ = true;
	elecUsageTimer_ = 0.0f;

	mainRenderer_->SetImage("NoElecStatic.png", true);
	fanRenderer_->Off();

	if (true == isRdoorClosed_)
	{
		rDoorRenderer_->SetChangeAnimation("RdoorOpen");
		isRdoorClosed_ = false;
	}

	if (true == isLdoorClosed_)
	{
		lDoorRenderer_->SetChangeAnimation("LdoorOpen");
		isLdoorClosed_ = false;
	}

	return StateInfo();
}

StateInfo GameController::updateNoElec(StateInfo _state)
{

// 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ���߰� ȭ���� �����ȴ�
// ���� 2�ʸ��� 1 / 5 Ȯ���� ������ �������ɾ�

	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();



	if (4 == noElecTimerCounter_)
	{
		return "HeisComing";
	}

	if (5.0f <= noElecDeltaTime_)
	{	// ������ ���� ���� 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ����Ǳ� �����ϰ�
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "HeisComing";
		}
		break;
		default:
			break;
		}
	}

	return StateInfo();
}


StateInfo GameController::startHeisComing(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;
	lDoorRenderer_->Off();
	rDoorRenderer_->Off();
	mainRenderer_->SetChangeAnimation("NoElec");
	return StateInfo();
}

StateInfo GameController::updateHeisComing(StateInfo _state)
{
	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (4 == noElecTimerCounter_)
	{
		return "HeKillsYou";
	}

	if (5.0f <= noElecDeltaTime_)
	{	// ������ ���� ���� 5�ʸ��� 1 / 5 Ȯ����(�ִ� 20��) �뷡�� ����Ǳ� �����ϰ�
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "HeKillsYou";
		}
		break;
		default:
			break;
		}
	}
	return StateInfo();
}

StateInfo GameController::startHeKillsYou(StateInfo _state)
{
	noElecDeltaTime_ = 0.0f;
	noElecTimerCounter_ = 0;
	mainRenderer_->SetChangeAnimation("NoElecBlink");
	return StateInfo();
}

StateInfo GameController::updateHeKillsYou(StateInfo _state)
{
	noElecDeltaTime_ += GameEngineTime::GetInst().GetDeltaTime();

	if (2.0f <= noElecDeltaTime_)
	{
		int dice = randomGenerator_.RandomInt(0, 4);

		switch (dice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_++;
			return StateInfo();
		}
		break;
		case 4:
		{
			noElecDeltaTime_ = 0.0f;
			noElecTimerCounter_ = 0;
			return "NoElecDeath";
		}
		break;
		default:
			break;
		}
	}
	return StateInfo();
	return StateInfo();
}

StateInfo GameController::startNoElecDeath(StateInfo _state)
{
	mainRenderer_->SetChangeAnimation("NoElecFreddy");
	return StateInfo();
}

StateInfo GameController::updateNoElecDeath(StateInfo _state)
{
	if (true == mainRenderer_->IsCurAnimationEnd())
	{
		GetLevel()->RequestLevelChange("GameOver");
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




void GameController::CollisionCCTVButton(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		// ������� �ٷ� ��ȯ �����ϰ�
		if (PLAYERSTATUS::OFFICE != CurPlayerState_)
		{

			UIController_->SwitchUIState(PLAYERSTATUS::OFFICE);
			state_.ChangeState("CCTVClose");
			return;
		}
		state_.ChangeState("CCTVOpen");
		return;
	}


	return;
}


void GameController::CollisionMuteCall(GameEngineCollision* _other)
{

}

void GameController::CollisionCam1A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::SHOWSTAGE;
	}
}

void GameController::CollisionCam1B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::DININGAREA;
	}
}

void GameController::CollisionCam1C(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::PIRATECOVE;
	}
}

void GameController::CollisionCam3(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::SUPPLYCLOSET;
	}
}

void GameController::CollisionCam5(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::BACKSTAGE;
	}
}

void GameController::CollisionCam2A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::WESTHALLA;
	}
}

void GameController::CollisionCam2B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::WESTHALLB;
	}
}

void GameController::CollisionCam7(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::RESTROOMS;
	}
}

void GameController::CollisionCam6(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::KITCHEN;
	}
}

void GameController::CollisionCam4A(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::EASTHALLA;
	}
}
void GameController::CollisionCam4B(GameEngineCollision* _other)
{
	if (true == GameEngineInput::GetInst().Down("MOUSE_1"))
	{
		CurCCTVState_ = LOCATION::EASTHALLB;
	}
}
