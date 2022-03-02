#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

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

