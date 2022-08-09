#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase\GameEngineThreadQueue.h>


// 게임의 핵심 구동부로 모든 씬(레벨)을 관리합니다.
// "MainCore" 하나만이 싱글톤으로 생성되며, Start() 로 구동을 시작합니다.

class GameEngineCore : public GameEngineObjectBase
{
	friend class GameEngineLevelControlWindow;

public:
	static GameEngineThreadQueue ThreadQueue;


	// ============================================= Level 관리자 관련 ============================================= //
private:
	static GameEngineLevel* NextLevel_;
	static GameEngineLevel* CurrentLevel_;
	static std::map<std::string, GameEngineLevel*> AllLevel_;


public:
	template<typename LevelType>
	static void LevelCreate(const std::string& _Level)
	{
		if (nullptr != LevelFind(_Level))
		{
			GameEngineDebug::MsgBoxError("같은 이름의 레벨을 2번 만들려고 했습니다");
			return;
		}

		AllLevel_.insert(std::make_pair(_Level, new LevelType()));
		AllLevel_[_Level]->Init();
		AllLevel_[_Level]->LevelStart();
	}

	static GameEngineLevel* CurrentLevel()
	{
		return CurrentLevel_;
	}

public:
	static void LevelChange(const std::string& _Level);
	static GameEngineLevel* LevelFind(const std::string& _Level);

	// ============================================== GameCore 관련 ============================================== //
private:
	static GameEngineCore* MainCore_;

private:
	static void WindowCreate(GameEngineCore& _RuntimeCore);
	static void Loop();
	static void MainLoop();

public:
	template<typename UserGameType>
	static void Start()
	{

		// 릭을 체크합니다. 디버깅이 중지될 시 남은 릭을 출력합니다.
		GameEngineDebug::LeakCheckOn();

#ifdef _DEBUG
		new int(); // 디버깅 중에는 무조건 릭이 4바이트 남게 처리했습니다.
#endif
		// 실제 게임 객체를 생성합니다. 템플릿으로 만들었으나 현재 프레임워크에선 "Usergame" 클래스가 자리잡습니다.
		UserGameType NewUserGame;

		// 윈도우창을 생성합니다. 
		WindowCreate(NewUserGame);


		NewUserGame.EngineInitialize();
		// 엔진 초기화 단계
		// 1. 다이렉트X11 디바이스를 생성합니다.
		// 2. 디바이스에서 스왑체인 구조를 생성합니다.
		// 3. 게임이 아닌 "엔진" 단계의 최소한의 리소스들을 로드합니다.
		// 4. IMGUI 로딩합니다.
		// 5. FMOD SDK 를 로딩합니다.
		// 6. "콜리젼 개념" 이 도입됩니다.


		NewUserGame.ResourcesLoad();
		// 본 게임 등급의 리소스들을 모두 로드해줍니다.
		// 시험적으로 스레드를 도입했으나 아직 미완성...


		// 씬 및 키 인풋 생성
		NewUserGame.Initialize();

		// 메인코어 == 유저게임 세팅!
		MainCore_ = &NewUserGame;

		// 게임의 메인 루프입니다.
		Loop();

		// 루프가 끝났다 == 게임 프로그램이 종료되었다
		// 엔진 메모리 소멸
		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

protected:
	GameEngineCore(); // default constructer 디폴트 생성자
	~GameEngineCore(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void EngineInitialize();
	void EngineResourcesLoad();
	void EngineResourcesCreate();
	void EngineDestroy();

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void Release() = 0;
	virtual float4 StartWindowSize() = 0;
	virtual float4 StartWindowPos() = 0;
};

