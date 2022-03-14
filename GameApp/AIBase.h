#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ENUM.h"

// 분류 : 
// 용도 : 
// 설명 : 

class AIBase : public GameEngineActor
{
public:
	AIBase(); 
	~AIBase();
	AIBase(const AIBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	AIBase(AIBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	AIBase& operator=(const AIBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	AIBase& operator=(const AIBase&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	float AILevel_;
	float actionFrequency_;
	LOCATION curLocation_;
	LOCATION nextLocation_;


};

