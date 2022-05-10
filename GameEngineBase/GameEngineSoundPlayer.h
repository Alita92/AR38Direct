#pragma once
#include "FMOD/fmod.hpp"
#include "GameEngineSound.h"
#include "GameEngineSoundManager.h"

// �з� :
// �뵵 :
// ���� :
class GameEngineSoundPlayer
{
	friend GameEngineSoundManager;

public:	// member Var
	GameEngineSoundManager* playSoundFile_;
	FMOD::Channel* playChannel_; // 
	int PlayCount;
	bool isStop_;

public:
	GameEngineSoundPlayer(); // default constructer ����Ʈ ������
	~GameEngineSoundPlayer(); // default destructer ����Ʈ �Ҹ���

public:		// delete constructer
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

public:		//delete operator
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSoundPlayer& operator=(const GameEngineSoundPlayer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:		//member Func
	bool IsPlay();
	bool IsStop();
	void PlayCountReset(int _Count = -1);

	// ���ļ� ��� ������ ���尡 ����ǰ� �־ �׳� ����Ѵ�. OneShot.
	void PlayOverLap(const std::string& _name, int _LoopCount = 0);

	// ������ ���尡 ����� �����߸� ���� ���带 ����Ѵ�.
	void PlayAlone(const std::string& _name, int _LoopCount = 0);
	void Stop();
	FMOD::Channel* GetChannel();
};

