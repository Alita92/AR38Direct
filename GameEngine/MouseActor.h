#pragma once
#include "GameEngineActor.h"
#include "GameEngineUIRenderer.h"


class MouseActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseActor();
	~MouseActor();

	// delete Function
	MouseActor(const MouseActor& _Other) = delete;
	MouseActor(MouseActor&& _Other) noexcept = delete;
	MouseActor& operator=(const MouseActor& _Other) = delete;
	MouseActor& operator=(MouseActor&& _Other) noexcept = delete;

	void SetCurSor(std::string _Name);
	void SetCurSor(std::string _Name, int _Index);

	GameEngineUIRenderer* GetUIRenderer()
	{
		return UIRenderer_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	GameEngineUIRenderer* UIRenderer_;

};

