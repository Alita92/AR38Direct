#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

#include <DirectXCollision.h>
#include <DirectXCollision.inl>

// 이녀석들만의 그룹을 만들겠습니다.

enum class CollisionType
{
	Sphere,
	AABBBox,
	OBBBox,
	MAX,
};

// 설명 :
class GameEngineLevel;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;


	template<typename UserType>
	void SetCollisionGroup(UserType _Type) // Enum 으로 들어왔을 시
	{
		SetCollisionGroup(static_cast<int>(_Type));
	}

	void SetCollisionGroup(int _Type); // 타입을 순번으로 정해준다

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::vector<GameEngineCollision*>& _Other);
	// 

	void Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack);


protected:


private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

