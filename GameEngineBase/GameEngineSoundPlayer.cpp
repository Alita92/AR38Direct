#include "PreCompile.h"
#include "GameEngineSoundPlayer.h"
#include "GameEngineSound.h"
#include "GameEngineDebug.h"


// Static Var
// Static Func

// constructer destructer
GameEngineSoundPlayer::GameEngineSoundPlayer()
	: playSoundFile_(nullptr)
	, playChannel_(nullptr)
	, PlayCount(-1)
	, isStop_(true)
{
	
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSoundPlayer&& _other) noexcept
	: playSoundFile_(_other.playSoundFile_)
	, playChannel_(_other.playChannel_)
	, PlayCount(_other.PlayCount)
{
}

//member Func

bool GameEngineSoundPlayer::IsPlay()
{
	bool Check = false;
	// �� FMOD�� §����� �׳� �̷��� §�ſ���.
	playChannel_->isPlaying(&Check);
	return Check;
}

bool GameEngineSoundPlayer::IsStop()
{
	return isStop_;
}

void GameEngineSoundPlayer::PlayCountReset(int _Count /*= -1*/)
{
	PlayCount = _Count;
}

void GameEngineSoundPlayer::PlayOverLap(const std::string& _name, int _LoopCount/* = 1*/)
{
	isStop_ = false;

	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);

	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);

}

void GameEngineSoundPlayer::PlayAlone(const std::string& _name, int _LoopCount /*= 1*/)
{
	isStop_ = false;
	// �Լ��� ���� ���Լ��� �ٽ� ����
	GameEngineSound* SoundPtr = GameEngineSoundManager::GetInst().FindSound(_name);

	if (nullptr == SoundPtr)
	{
		GameEngineDebug::MsgBoxError("PlaySound Error");
		return;
	}

	if (true == IsPlay())
	{
		return;
	}

	if (0 == PlayCount)
	{
		return;
	}

	GameEngineSoundManager::GetInst().soundSystem_->playSound(
		SoundPtr->sound_
		, nullptr
		, false
		, &playChannel_);

	--PlayCount;

	playChannel_->setLoopCount(_LoopCount);
}


void GameEngineSoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	playChannel_->stop();
	playChannel_ = nullptr;
	isStop_ = true;
}

FMOD::Channel* GameEngineSoundPlayer::GetChannel()
{
	return playChannel_;
}