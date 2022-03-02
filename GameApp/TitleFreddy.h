#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// 설명 : 타이틀 레벨의 배경 화면에 움직이는 프레디의 스프라이트와 애니메이션입니다.
//		  뒷배경을 대체합니다.

class GameEngineImageRenderer;
class TitleFreddy : public GameEngineActor
{
public:
	TitleFreddy(); // default constructer 디폴트 생성자
	~TitleFreddy(); // default destructer 디폴트 소멸자

	TitleFreddy(const TitleFreddy& _other) = delete;
	TitleFreddy(TitleFreddy&& _other) noexcept;
	TitleFreddy& operator=(const TitleFreddy& _other) = delete; 
	TitleFreddy& operator=(const TitleFreddy&& _other) noexcept = delete;

protected:
	GameEngineImageRenderer* titleFreddyImageRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	GameEngineRandom randomGenerator_;
	int timeDice_;
	int faceDice_;
	float generalInterTime_;
	float facialChangeInterTime_;
	bool isFirstSessionOut_;

public:
	void FreddyFacialChange();
	void RandomImageChange();
};

