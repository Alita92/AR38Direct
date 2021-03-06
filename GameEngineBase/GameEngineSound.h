#pragma once
#include "GameEngineSoundManager.h"
#include "GameEngineObjectNameBase.h"

// 분류 :
// 용도 :
// 설명 :
class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineObjectNameBase
{
	friend GameEngineSoundManager;
	friend GameEngineSoundPlayer;

private:	// member Var
	FMOD::Sound* sound_;

public:
	bool Load(const std::string& _Path);


private:
	GameEngineSound(); // default constructer 디폴트 생성자
	~GameEngineSound(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineSound(const GameEngineSound& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSound(GameEngineSound&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineSound& operator=(const GameEngineSound& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSound& operator=(const GameEngineSound&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
};

