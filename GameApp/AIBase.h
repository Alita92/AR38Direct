#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ENUM.h"

// �з� : 
// �뵵 : 
// ���� : 

class AIBase : public GameEngineActor
{
public:
	AIBase(); 
	~AIBase();
	AIBase(const AIBase& _other) = delete; // default Copy constructer ����Ʈ ���������
	AIBase(AIBase&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	AIBase& operator=(const AIBase& _other) = delete; // default Copy operator ����Ʈ ���� ������
	AIBase& operator=(const AIBase&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	float AILevel_;
	float actionFrequency_;
	LOCATION curLocation_;
	LOCATION nextLocation_;


};

