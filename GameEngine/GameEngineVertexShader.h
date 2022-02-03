#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDirectXDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineVertexShader : public GameEngineObjectNameBase
{
private:	// member Var
	UINT VersionHigh_; // 버텍스의 버전(소수점 앞자리)
	UINT VersionLow_; // 버텍스의 버전(소수점 뒷자리)
	ID3DBlob* CodeBlob_;
	std::string Version_;

	std::string EntryPoint_;
	// shader program의 entry 함수의 이름
	// 하나의.hlsl 파일에 여러개의 shader program이 있을 수 있으므로(예를들어 정점 셰이더 하나, 픽셀 셰이더 하나), 컴파일할 특정 shader의 진입점을 명시해야 한다

	std::string Code_;

public:


	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	bool Create(
		const std::string& _ShaderCode,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);
	bool Compile();
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);


private:
	void CreateVersion();

	/// <summary>
	/// ////////////////////////////// InputLayOutSettting
	/// </summary>

private:
	ID3D11InputLayout* LayOut_;
	unsigned int LayOutOffset_;
	std::vector<std::string> SemanticName_;
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayoutDesc_;

public:
	void AddInputLayOut(
		const char* _SemanticName,
		unsigned int _Index,
		unsigned int _AlignedByteOffset,
		DXGI_FORMAT _Format,
		unsigned int _InputSlot,
		unsigned int _InstanceDataStepRate,
		D3D11_INPUT_CLASSIFICATION _inputClass
	);

	void CreateLayOut();
	void LayOutClear();
};

