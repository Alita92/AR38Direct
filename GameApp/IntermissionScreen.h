#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class IntermissionController;
class GameEngineImageRenderer;
class IntermissionScreen : public GameEngineActor
{
private:
	friend IntermissionController;

public:
	IntermissionScreen(); // default constructer 디폴트 생성자
	~IntermissionScreen(); // default destructer 디폴트 소멸자
	IntermissionScreen(const IntermissionScreen& _other) = delete; // default Copy constructer 디폴트 복사생성자
	IntermissionScreen(IntermissionScreen&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	IntermissionScreen& operator=(const IntermissionScreen& _other) = delete; // default Copy operator 디폴트 대입 연산자
	IntermissionScreen& operator=(const IntermissionScreen&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	GameEngineImageRenderer* mainRenderer_;
	// 스크린 전체를 렌더하는 배경색

	GameEngineImageRenderer* typoRenderer_;
	// DAY 타이포를 렌더합니다.

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

