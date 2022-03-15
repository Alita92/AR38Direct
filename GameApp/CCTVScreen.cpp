#include "PreCompile.h"
#include "CCTVScreen.h"
#include <GameEngine/GameEngineImageRenderer.h>

CCTVScreen::CCTVScreen() // default constructer 디폴트 생성자
	: mainRenderer_(nullptr), subRenderer_(nullptr)
	, curScreen_(LOCATION::MAX)
{

}

CCTVScreen::~CCTVScreen() // default destructer 디폴트 소멸자
{

}

void CCTVScreen::Start()
{
	curScreen_ = LOCATION::SHOWSTAGE;
}

void CCTVScreen::Update(float _DeltaTime)
{

}

void CCTVScreen::SetScreenTo(LOCATION _location)
{
	switch (_location)
	{
	case LOCATION::OFFICE:
	case LOCATION::LOFFICEDOOR:
	case LOCATION::ROFFICEDOOR:
	{
		GameEngineDebug::MsgBoxError("잘못된 CCTV 설정이 들어왔습니다");
	}
		break;
	case LOCATION::SHOWSTAGE:
	{
		curScreen_ = LOCATION::SHOWSTAGE;
	}
		break;
	case LOCATION::KITCHEN:
	{
		curScreen_ = LOCATION::KITCHEN;
	}
		break;
	case LOCATION::BACKSTAGE:
	{
		curScreen_ = LOCATION::BACKSTAGE;
	}
		break;
	case LOCATION::DININGAREA:
	{
		curScreen_ = LOCATION::DININGAREA;
	}
		break;
	case LOCATION::PIRATECOVE:
	{
		curScreen_ = LOCATION::PIRATECOVE;
	}
		break;
	case LOCATION::EASTHALLA:
	{
		curScreen_ = LOCATION::EASTHALLA;
	}
		break;
	case LOCATION::EASTHALLB:
	{
		curScreen_ = LOCATION::EASTHALLB;
	}
		break;
	case LOCATION::WESTHALLA:
	{
		curScreen_ = LOCATION::WESTHALLA;
	}
		break;
	case LOCATION::WESTHALLB:
	{
		curScreen_ = LOCATION::WESTHALLB;
	}
		break;
	case LOCATION::RESTROOMS:
	{
		curScreen_ = LOCATION::RESTROOMS;
	}
		break;
	case LOCATION::SUPPLYCLOSET:
	{
		curScreen_ = LOCATION::SUPPLYCLOSET;
	}
		break;
	case LOCATION::NONE:
		break;
	case LOCATION::MAX:
		break;
	default:
		break;
	}




}

void CCTVScreen::SetScreenImage(std::string _imageName)
{
	mainRenderer_->SetImage(_imageName, true);
}