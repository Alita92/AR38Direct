#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase\GameEngineThreadQueue.h>


// ������ �ٽ� �����η� ��� ��(����)�� �����մϴ�.
// "MainCore" �ϳ����� �̱������� �����Ǹ�, Start() �� ������ �����մϴ�.

class GameEngineCore : public GameEngineObjectBase
{
	friend class GameEngineLevelControlWindow;

public:
	static GameEngineThreadQueue ThreadQueue;


	// ============================================= Level ������ ���� ============================================= //
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
			GameEngineDebug::MsgBoxError("���� �̸��� ������ 2�� ������� �߽��ϴ�");
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

	// ============================================== GameCore ���� ============================================== //
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

		// ���� üũ�մϴ�. ������� ������ �� ���� ���� ����մϴ�.
		GameEngineDebug::LeakCheckOn();

#ifdef _DEBUG
		new int(); // ����� �߿��� ������ ���� 4����Ʈ ���� ó���߽��ϴ�.
#endif
		// ���� ���� ��ü�� �����մϴ�. ���ø����� ��������� ���� �����ӿ�ũ���� "Usergame" Ŭ������ �ڸ�����ϴ�.
		UserGameType NewUserGame;

		// ������â�� �����մϴ�. 
		WindowCreate(NewUserGame);


		NewUserGame.EngineInitialize();
		// ���� �ʱ�ȭ �ܰ�
		// 1. ���̷�ƮX11 ����̽��� �����մϴ�.
		// 2. ����̽����� ����ü�� ������ �����մϴ�.
		// 3. ������ �ƴ� "����" �ܰ��� �ּ����� ���ҽ����� �ε��մϴ�.
		// 4. IMGUI �ε��մϴ�.
		// 5. FMOD SDK �� �ε��մϴ�.
		// 6. "�ݸ��� ����" �� ���Ե˴ϴ�.


		NewUserGame.ResourcesLoad();
		// �� ���� ����� ���ҽ����� ��� �ε����ݴϴ�.
		// ���������� �����带 ���������� ���� �̿ϼ�...


		// �� �� Ű ��ǲ ����
		NewUserGame.Initialize();

		// �����ھ� == �������� ����!
		MainCore_ = &NewUserGame;

		// ������ ���� �����Դϴ�.
		Loop();

		// ������ ������ == ���� ���α׷��� ����Ǿ���
		// ���� �޸� �Ҹ�
		NewUserGame.Release();
		NewUserGame.EngineDestroy();
	}

protected:
	GameEngineCore(); // default constructer ����Ʈ ������
	~GameEngineCore(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

