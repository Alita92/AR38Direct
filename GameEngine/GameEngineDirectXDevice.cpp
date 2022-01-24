#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"

GameEngineDirectXDevice::GameEngineDirectXDevice() // default constructer ����Ʈ ������
	: Device_(nullptr)
	, Context_(nullptr)
	, SwapChain_(nullptr)
{

}

GameEngineDirectXDevice::~GameEngineDirectXDevice() // default destructer ����Ʈ �Ҹ���
{
	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}
}

void GameEngineDirectXDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window HWND Error");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG //����, ����׷� ��������...
	iFlag = D3D11_CREATE_DEVICE_DEBUG;  // �� ���� ���ļ� iFlag ���� �ٲ� �ش�.
#endif // _DEBUG

	// ���� ����ϴ� ���̷�Ʈ ���������� �ʱ�ȭ���ش�.
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// D3D_FEATURE_LEVEL eLVArr[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0;
	// ���� ���� ������ ���༱���ϰ� ���� ���� ���� �ڵ带 ����ϸ� �ȴ�.
	
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE <= ���� ����� GPU�� �������� ��.
	// SOFTWARE �� �ô� CPU
	if (
		S_OK != D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			iFlag,
			nullptr, // eLVArr
			0,
			D3D11_SDK_VERSION,
			&Device_,
			&eLV,
			&Context_)
		)
	{
		GameEngineDebug::MsgBoxError("D3D11 Create Device ERROR");
	}

	if (eLV != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxError("D3D11 Not FEATURE LEVEL 11 ERROR");
	}

	CreateSwapChain(); // HWND ����, ����̽� ���ؽ�Ʈ ������ ������ ������۸��� ������ش�.
}

void GameEngineDirectXDevice::CreateSwapChain() // ���̷�ƮX ����� ������۸� �ý����� ������ش�.
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x &&
		0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		// (�׷� ���� ��������) ��ũ�� ����� ���̳ʽ� ���϶��� ����...
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize(); // �ػ� ����� �����´�.

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, };

	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy(); // ������ ����� �������ְ�..

	// ����Ϳ� �����ؼ�
	ScInfo.BufferDesc.RefreshRate.Denominator = 1.0f;
	// Denominator == �и� == xx�ʴ�
	ScInfo.BufferDesc.RefreshRate.Numerator = 60.0f;
	// Numerator == ���� == xx���� �ֻ����� �������ش�.
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
}
