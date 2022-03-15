#pragma once
#include <GameEngine/GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 

class GameEngineImageRenderer;
class OfficeTest : public GameEngineActor
{
private:	// member Var

public:
	OfficeTest(); 
	~OfficeTest(); 
	OfficeTest(const OfficeTest& _other) = delete;
	OfficeTest(OfficeTest&& _other) noexcept;
	OfficeTest& operator=(const OfficeTest& _other) = delete;
	OfficeTest& operator=(const OfficeTest&& _other) = delete;

protected:
	GameEngineImageRenderer* mainRenderer_;

	GameEngineImageRenderer* lDoorRenderer_;
	GameEngineImageRenderer* rDoorRenderer_;

	GameEngineImageRenderer* fanRenderer_;


private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitAnimation();
};

