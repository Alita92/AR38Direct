#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class TitleController;
class GameEngineImageRenderer;
class GameEngineBackgroundRenderer;
class TitleNewsPaper : public GameEngineActor
{
private:
	friend TitleController;

public:
	TitleNewsPaper(); // default constructer ����Ʈ ������
	~TitleNewsPaper(); // default destructer ����Ʈ �Ҹ���
	TitleNewsPaper(const TitleNewsPaper& _other) = delete; // default Copy constructer ����Ʈ ���������
	TitleNewsPaper(TitleNewsPaper&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	TitleNewsPaper& operator=(const TitleNewsPaper& _other) = delete; // default Copy operator ����Ʈ ���� ������
	TitleNewsPaper& operator=(const TitleNewsPaper&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	GameEngineImageRenderer* newsPaperRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

