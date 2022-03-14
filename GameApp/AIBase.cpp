#include "PreCompile.h"
#include "AIBase.h"

AIBase::AIBase() // default constructer 디폴트 생성자
	: actionFrequency_(0.0f), AILevel_(0.0f), curLocation_(LOCATION::MAX), nextLocation_(LOCATION::MAX)
{

}

AIBase::~AIBase() // default destructer 디폴트 소멸자
{

}

