#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"
// DirectXTex 헤더 추가!

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture : public GameEngineObjectNameBase
{
public:
	void Create(ID3D11Texture2D* _Texture2D);
	void Load(const std::string& _Path);

	ID3D11RenderTargetView* CreateRenderTargetView();


	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11ShaderResourceView** GetShaderResourcesView();

	GameEngineTexture(); // default constructer 디폴트 생성자
	~GameEngineTexture(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineTexture(const GameEngineTexture& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자ㅏㅒ


	D3D11_TEXTURE2D_DESC TextureDesc_; // 텍스처의 기본 설정값 저장하는 변수
	ID3D11Texture2D* Texture2D_; // 들고 있는 텍스처
	ID3D11RenderTargetView* RenderTargetView_; // 렌더타겟 뷰 저장 변수
	ID3D11ShaderResourceView* ShaderResourceViewPtr_; // 셰이더 리소스 뷰 변수


	DirectX::ScratchImage Image_;
};

