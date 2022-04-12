#pragma once
#include <GameEngine\GameEnginePostProcessRender.h>

// Ό³Έν :
class CurvedEffect : public GameEnginePostProcessRender
{
public:
	// constrcuter destructer
	CurvedEffect(GameEngineRenderTarget* RenderTarget);
	~CurvedEffect();

	// delete Function
	CurvedEffect(const CurvedEffect& _Other) = delete;
	CurvedEffect(CurvedEffect&& _Other) noexcept = delete;
	CurvedEffect& operator=(const CurvedEffect& _Other) = delete;
	CurvedEffect& operator=(CurvedEffect&& _Other) noexcept = delete;

protected:
	void Effect(float _DeltaTime) override;
	void Initialize() override;

private:

};

