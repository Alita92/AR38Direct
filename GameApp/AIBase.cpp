#include "PreCompile.h"
#include "AIBase.h"

AIBase::AIBase() // default constructer ����Ʈ ������
	: actionFrequency_(0.0f), AILevel_(0.0f), curLocation_(LOCATION::MAX), nextLocation_(LOCATION::MAX)
{

}

AIBase::~AIBase() // default destructer ����Ʈ �Ҹ���
{

}

