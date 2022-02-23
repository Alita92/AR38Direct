#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"
// DirectXTex ��� �߰�!

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture : public GameEngineObjectNameBase
{
public:
	void Create(ID3D11Texture2D* _Texture2D);
	void Load(const std::string& _Path);

	ID3D11RenderTargetView* CreateRenderTargetView();


	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11ShaderResourceView** GetShaderResourcesView();

	GameEngineTexture(); // default constructer ����Ʈ ������
	~GameEngineTexture(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineTexture(const GameEngineTexture& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ����ڤ���


	D3D11_TEXTURE2D_DESC TextureDesc_; // �ؽ�ó�� �⺻ ������ �����ϴ� ����
	ID3D11Texture2D* Texture2D_; // ��� �ִ� �ؽ�ó
	ID3D11RenderTargetView* RenderTargetView_; // ����Ÿ�� �� ���� ����
	ID3D11ShaderResourceView* ShaderResourceViewPtr_; // ���̴� ���ҽ� �� ����


	DirectX::ScratchImage Image_;
};

