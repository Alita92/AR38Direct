#pragma once
#include <GameEngine/GameEngineActor.h>
// 분류 : 
// 용도 : 
// 설명 : 

class GameEngineImageRenderer;
class OfficeFan : public GameEngineActor
{
public:
	OfficeFan(); // default constructer 디폴트 생성자
	~OfficeFan(); // default destructer 디폴트 소멸자
	OfficeFan(const OfficeFan& _other) = delete; // default Copy constructer 디폴트 복사생성자
	OfficeFan(OfficeFan&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	OfficeFan& operator=(const OfficeFan& _other) = delete; // default Copy operator 디폴트 대입 연산자
	OfficeFan& operator=(const OfficeFan&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	GameEngineImageRenderer* mainRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitAnimation();
};

