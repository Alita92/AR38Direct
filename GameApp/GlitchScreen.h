#pragma once
#include <GameEngine/GameEngineActor.h>
// �з� : 
// �뵵 : 
// ���� : 

class TitleController;
class IntermissionController;
class GameController;
class GameEngineImageRenderer;
class GameEngineUIRenderer;
class GlitchScreen : public GameEngineActor
{
private:
	friend TitleController;
	friend IntermissionController;
	friend GameController;

public:
	GlitchScreen(); // default constructer ����Ʈ ������
	~GlitchScreen(); // default destructer ����Ʈ �Ҹ���
	GlitchScreen(const GlitchScreen& _other) = delete; // default Copy constructer ����Ʈ ���������
	GlitchScreen(GlitchScreen&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������
	GlitchScreen& operator=(const GlitchScreen& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GlitchScreen& operator=(const GlitchScreen&& _other) noexcept = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void PlayWhiteNoise(bool _on);
	void SetStatic();
	void PlayAwakeScanLine();

protected:
	GameEngineImageRenderer* whiteNoiseRenderer_;
	GameEngineImageRenderer* scanLineRenderer_;

private:
	void Start() override;
	void Update(float _Deltatime) override;

private:
	void ImageInit();
	
};

