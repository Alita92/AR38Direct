#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRenderingPipeLine
{
	// 랜더링 파이프라인은 "모니터에 나오기 위한" 절차가 아닌
	//	"백버퍼에 기설정된 값을 넣는 거임!!!" * **
	// 액터마다 각자 하나씩 가지고 있어야 한다.

private:	// member Var
	// 

	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineVertexShader* VertexShader_;

public:
	void SetInputAssembler1(GameEngineVertexBuffer* _Ptr);

	void SetVertexShader(GameEngineVertexShader* _Ptr);

public:
	void Rendering();


public:
	GameEngineRenderingPipeLine(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLine(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

