#pragma once
#include "FMOD/fmod.hpp"
#include <list>
#include <map>
#include <string>

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib") // Debug 용 빌드된 코드파일
#else
#pragma comment(lib, "fmod_vc.lib") // Release용 빌드된 코드파일
#endif

// 이런 사운드 이미지 리소스 폰트 우리가 로드하거나 
// 구현할줄 몰르거나 너무 귀찮아서 사용하는 라이브러리들

// 단계가 다음과 같다.
// 이니셜라이즈 함수를 찾는다. <= 대부분 그 라이브러의 전체 총괄 시스템용 객체가 존재한다.
// 릴리즈함수에요.
// 로드 함수를 찾아야한다.
// 그다음에 랜더링이나 재생함수를 찾아야 합니다.


#include <unordered_map>

class GameEngineSoundPlayer;
class GameEngineSoundManager
{
	friend GameEngineSoundPlayer;
public:
	~GameEngineSoundManager();

	GameEngineSoundManager(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager(GameEngineSoundManager&& _other) = delete;

	GameEngineSoundManager& operator=(const GameEngineSoundManager& _other) = delete;
	GameEngineSoundManager& operator=(const GameEngineSoundManager&& _other) = delete;

public:
	static GameEngineSoundManager& GetInstance() { return *instance_; }
	static void Destroy();

	void Initialize();
	void Update();

	void CreateSound(const std::string& _name, const std::string& _path, bool _bLoop = false);

	void PlaySoundByName(const std::string& _name);
	void SetVolume(unsigned int _volume);
	void StopSound();

private:
	GameEngineSoundManager();

	FMOD::Sound* getSound(const std::string& _name);

private:
	static GameEngineSoundManager* instance_;

private:
	FMOD::System* system_;
	FMOD::Channel* channel_;

	std::unordered_map<std::string, FMOD::Sound*> allSounds_;
};

