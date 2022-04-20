#pragma once
#include <GameEngine/GameEngineCore.h>

class UserGame : public GameEngineCore
{
private:	
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

