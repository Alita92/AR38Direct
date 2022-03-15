#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ENUM.h"
// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class CCTVScreen : public GameEngineActor
{
public:
	CCTVScreen();
	~CCTVScreen(); 
	CCTVScreen(const CCTVScreen& _other) = delete; 
	CCTVScreen(CCTVScreen&& _other) noexcept; 
	CCTVScreen& operator=(const CCTVScreen& _other) = delete;
	CCTVScreen& operator=(const CCTVScreen&& _other) noexcept = delete; 

private:
	void Start() override;
	void Update(float _Deltatime) override;

protected:
	GameEngineImageRenderer* mainRenderer_;
	GameEngineImageRenderer* subRenderer_;

private:
	LOCATION curScreen_;

public:
	void SetScreenTo(LOCATION _location);
	void SetScreenImage(std::string _imageName);

};

