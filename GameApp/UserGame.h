#pragma once
#include <GameEngine/GameEngineCore.h>

class UserGame : public GameEngineCore
{
public:
	// 락이 걸리지 않는다.
	// 락이 걸리는데 가벼운 락이 걸려서 빠르다.
	// 운영체제가 관리해주는 cpu 수준의 락을 거는데 이게 빠르다.
	// 64바이트
	static std::atomic<int> LoadingFolder;

public:
	UserGame(); 
	~UserGame(); 

protected:	
	UserGame(const UserGame& _other) = delete;
	UserGame(UserGame&& _other) noexcept;

private:		
	UserGame& operator=(const UserGame& _other) = delete; 
	UserGame& operator=(const UserGame&& _other) = delete; 

public:
	virtual void Initialize() override;
	virtual void ResourcesLoad() override;
	virtual void Release() override;
	void KeyInit();

	virtual float4 StartWindowPos() {
		return { 0, 0 };
	}
	virtual float4 StartWindowSize() {
		return { 1280, 720 };
	}
};

