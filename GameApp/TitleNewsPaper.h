#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class TitleController;
class GameEngineImageRenderer;
class GameEngineBackgroundRenderer;
class TitleNewsPaper : public GameEngineActor
{
private:
	friend TitleController;

public:
	TitleNewsPaper(); // default constructer 디폴트 생성자
	~TitleNewsPaper(); // default destructer 디폴트 소멸자
	TitleNewsPaper(const TitleNewsPaper& _other) = delete; // default Copy constructer 디폴트 복사생성자
	TitleNewsPaper(TitleNewsPaper&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자
	TitleNewsPaper& operator=(const TitleNewsPaper& _other) = delete; // default Copy operator 디폴트 대입 연산자
	TitleNewsPaper& operator=(const TitleNewsPaper&& _other) noexcept = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	GameEngineImageRenderer* newsPaperRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

