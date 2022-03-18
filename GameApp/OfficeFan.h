#pragma once
#include <GameEngine/GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 

class GameEngineImageRenderer;
class OfficeFan : public GameEngineActor
{
public:
	OfficeFan(); // default constructer ����Ʈ ������
	~OfficeFan(); // default destructer ����Ʈ �Ҹ���
	OfficeFan(const OfficeFan& _other) = delete; // default Copy constructer ����Ʈ ���������
	OfficeFan(OfficeFan&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	OfficeFan& operator=(const OfficeFan& _other) = delete; // default Copy operator ����Ʈ ���� ������
	OfficeFan& operator=(const OfficeFan&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* mainRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void InitAnimation();
};

