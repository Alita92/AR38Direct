#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineWindow.h"
#include "GameEngineTextureManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineDepthBufferManager.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineDepthBuffer.h"

GameEngineDevice* GameEngineDevice::Inst = new GameEngineDevice();

GameEngineRenderTarget* GameEngineDevice::BackBufferTarget_ = nullptr;
ID3D11Device* GameEngineDevice::Device_ = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context_ = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain_ = nullptr;

GameEngineRenderTarget* GameEngineDevice::GetBackBufferTarget()
{
	return BackBufferTarget_;
}


ID3D11Device* GameEngineDevice::GetDevice()
{
	return Device_;
}

ID3D11DeviceContext* GameEngineDevice::GetContext()
{
	return Context_;
}

GameEngineDevice::GameEngineDevice() // default constructer 디폴트 생성자
{

}

GameEngineDevice::~GameEngineDevice() // default destructer 디폴트 소멸자
{
	if (nullptr != SwapChain_)
	{
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}

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

void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window Hwnd ERROR");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 님이 사용하려는 다이렉트 버전이 몇인가요?
	// 다이렉트 11 사용합니다.
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// D3D_FEATURE_LEVEL eLVArr[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0;

	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE

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

	//CreateSwapChain();
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	
}

// 스왑체인 : DX환경에서의 화면 출력 방식을 관리해줌. 렌더 타겟을 잡아내는 역할?
void GameEngineDevice::CreateSwapChain() // 스왑체인을 "만드는" 행위는 공간 할당의 영역이니 디바이스가 담당!
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x &&
		0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, }; // 1. 공백의 스왑 체인 설정값을 객체화 및 이니셜라이징

	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy(); // 2. 화면 해상도와 일치하는 넓이(X) 높이(Y) 값을 설정.

	ScInfo.BufferDesc.RefreshRate.Denominator = 1; // 3. 기준초.
	ScInfo.BufferDesc.RefreshRate.Numerator = 60; // 4. 기준초 내 몇 번 백버퍼를 그릴 건지?
	// 현재로선 1초에 60번을 그리게 된다.

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 5. 이미지 색상은 한 색상 당 8바이트 내에서 그려주게 설정.
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // 6. 스케일링 방향. 그렇게 크게 상관 없을듯...
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT; // 7. 셰이더를 적용할건지, 적용할지 않을지...

	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1; // 8. 샘플링의 사용유무... true 면 사용, false 면 미사용

	ScInfo.OutputWindow = GameEngineWindow::GetInst().GetWindowHWND(); // 9 . 적용할 윈도우 창의 핸들값 가져오기.

	ScInfo.BufferCount = 2; // 10. 그려주는 버퍼의 수

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD; // 11. 디스플레이 화면의 픽셀을 처리하기 위한 옵션...
	// 백 버퍼 그려진 후의 버퍼를 DISCARD 한다?

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 	// 전체화면 모드 가능여부 설정

	ScInfo.Windowed = true; 	// 전체화면 안함.

	// 그래픽카드의 화면출력에 관련된 리소스에 관여할수 있는 
	// 기능들의 포인터를 얻어오고
	// 그 기능들을 통해서 백버퍼의 텍스처를 직업 얻어올 것이다.

	// ID3D11Device* != IDXGIDevice;
	// 그래픽카드의 메모리에 관리자를 접근한다..
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		GameEngineDebug::MsgBoxError("IDXGIDevice null");
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pA)
	{
		GameEngineDebug::MsgBoxError("IDXGIAdapter null");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		GameEngineDebug::MsgBoxError("IDXGIFactory null");
	}

	if (S_OK != pF->CreateSwapChain(Device_, &ScInfo, &SwapChain_))
	{
		GameEngineDebug::MsgBoxError("SwapChain Create Error");
	}

	pF->Release();
	pA->Release();
	pD->Release();

	ID3D11Texture2D* BackBufferTexture = nullptr;
	if (S_OK != SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture)))
	{
		GameEngineDebug::MsgBoxError("SwapChain Texture Error");
	}

	GameEngineTextureManager::GetInst().Create("BackBuffer", BackBufferTexture);
	BackBufferTarget_ = GameEngineRenderTargetManager::GetInst().Create("BackBuffer", "BackBuffer", float4::GREEN);

	// DepthBuffer_ = GameEngineDepthBufferManager::GetInst().Create("DeviceDepthBuffer", GameEngineWindow::GetInst().GetSize());
}

void GameEngineDevice::RenderStart()
{
	// BackBufferTarget_ <= 여기에 그린 녀석만 나와.
	// 지우고
	BackBufferTarget_->Clear();
	// 세팅하고
	BackBufferTarget_->Setting();
}


void GameEngineDevice::RenderEnd()
{
	// 화면에 그려라 인데.
	HRESULT Result = SwapChain_->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		int a = 0;
	}

	// 화면에 뿌려라
	// BackBufferTarget_;
}