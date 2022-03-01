#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� : Ÿ��Ʋ ������ ��� ȭ�鿡 �����̴� �������� ��������Ʈ�� �ִϸ��̼��Դϴ�.
//		  �޹���� ��ü�մϴ�.

class GameEngineImageRenderer;
class TitleFreddy : public GameEngineActor
{
public:
	TitleFreddy(); // default constructer ����Ʈ ������
	~TitleFreddy(); // default destructer ����Ʈ �Ҹ���

	TitleFreddy(const TitleFreddy& _other) = delete;
	TitleFreddy(TitleFreddy&& _other) noexcept;
	TitleFreddy& operator=(const TitleFreddy& _other) = delete; 
	TitleFreddy& operator=(const TitleFreddy&& _other) noexcept = delete;

protected:
	GameEngineImageRenderer* titleFreddyImageRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;
};

