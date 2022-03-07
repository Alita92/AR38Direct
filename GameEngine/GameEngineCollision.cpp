#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::Start()
{
	GetLevel()->PushCollision(this, GetOrder());
}

void GameEngineCollision::Update(float _DeltaTime)
{

}

void GameEngineCollision::SetCollisionGroup(int _Type)
{
	GetLevel()->ChangeCollisionGroup(_Type, this);
}

void GameEngineCollision::Collision(
	CollisionType _ThisType,
	CollisionType _OtherType,
	int _OtherGroup,
	std::vector<GameEngineCollision*>& _ColVector
)
{


	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

	DirectX::BoundingSphere ThisSphere;
	DirectX::BoundingSphere OtherSphere;
	// 다이렉트에서 제공하는 구체 구조체

	float4 Pos = GetTransform()->GetWorldPosition();
	float4 Scale = GetTransform()->GetWorldScaling() * 0.5f; // 반지름을 담기 위해 0.5를 곱한다.

	float4 OtherPos;
	float4 OtherScale;

	memcpy_s(&ThisSphere.Center, sizeof(ThisSphere.Center), &Pos, sizeof(ThisSphere.Center));
	memcpy_s(&ThisSphere.Radius, sizeof(float), &Scale, sizeof(float));
	// 구체 구조체의 값에 위치와 반지름값을 메모리카피로 넣어 준다.
	
	// 그 레벨의 콜리전 리스트를 쭉 타고 다니며...
	for (GameEngineCollision* OtherCollision : Group)
	{
		// 타고 다니며 만나는 콜리젼의 위치와 반지름을 측정하고..
		OtherPos = OtherCollision->GetTransform()->GetWorldPosition();
		OtherScale = OtherCollision->GetTransform()->GetLocalScaling() * 0.5f;

		// 이 역시 구체 구조체에 대입
		memcpy_s(&OtherSphere.Center, sizeof(ThisSphere.Center), &OtherPos, sizeof(ThisSphere.Center));
		memcpy_s(&OtherSphere.Radius, sizeof(float), &OtherScale, sizeof(float));

		// 
		if (false == ThisSphere.Intersects(OtherSphere))
		{
			continue;
		}

		_ColVector.push_back(OtherCollision);
	}
}

void GameEngineCollision::Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
{
	// 함수 포인터
	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

	DirectX::BoundingSphere ThisSphere;
	DirectX::BoundingSphere OtherSphere;

	float4 Pos = GetTransform()->GetWorldPosition();
	float4 Scale = GetTransform()->GetWorldScaling() * 0.5f;

	float4 OtherPos;
	float4 OtherScale;

	memcpy_s(&ThisSphere.Center, sizeof(ThisSphere.Center), &Pos, sizeof(ThisSphere.Center));
	memcpy_s(&ThisSphere.Radius, sizeof(float), &Scale, sizeof(float));

	for (GameEngineCollision* OtherCollision : Group)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		OtherPos = OtherCollision->GetTransform()->GetWorldPosition();
		OtherScale = OtherCollision->GetTransform()->GetLocalScaling() * 0.5f;

		memcpy_s(&OtherSphere.Center, sizeof(ThisSphere.Center), &OtherPos, sizeof(ThisSphere.Center));
		memcpy_s(&OtherSphere.Radius, sizeof(float), &OtherScale, sizeof(float));

		if (false == ThisSphere.Intersects(OtherSphere))
		{
			continue;
		}

		_CallBack(OtherCollision);
	}
}