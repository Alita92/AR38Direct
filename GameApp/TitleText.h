#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

// 분류 : 
// 용도 : 
// 설명 :
class GameEngineImageRenderer;
class TitleText : public GameEngineActor
{
public:
	TitleText(); 
	~TitleText();
	TitleText(const TitleText& _other) = delete;
	TitleText(TitleText&& _other) noexcept;
	TitleText& operator=(const TitleText& _other) = delete;
	TitleText& operator=(const TitleText&& _other) noexcept = delete;

protected:
	// 띄우기만 하면 됨
	GameEngineImageRenderer* titleName_;
	GameEngineImageRenderer* titleScott_;

	// 충돌체 있어야 함
	GameEngineImageRenderer* titleNewGame_;
	GameEngineImageRenderer* titleContinue_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

