#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"
#include "GameEngineTextureManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineRenderTarget.h"

GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();
GameEngineRenderTarget* GameEngineDirectXDevice::BackBufferTarget_ = nullptr;
ID3D11Device* GameEngineDirectXDevice::Device_ = nullptr;
ID3D11DeviceContext* GameEngineDirectXDevice::Context_ = nullptr;
IDXGISwapChain* GameEngineDirectXDevice::SwapChain_ = nullptr;

ID3D11Device* GameEngineDirectXDevice::GetDevcie()
{
	return Device_;
}

ID3D11DeviceContext* GameEngineDirectXDevice::GetContext()
{
	return Context_;
}

GameEngineDirectXDevice::GameEngineDirectXDevice() // default constructer 디폴트 생성자
{

}

GameEngineDirectXDevice::~GameEngineDirectXDevice() // default destructer 디폴트 소멸자
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

void GameEngineDirectXDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window HWND Error");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG //만약, 디버그로 빌드실행시...
	iFlag = D3D11_CREATE_DEVICE_DEBUG;  // 이 곳을 거쳐서 iFlag 값을 바꿔 준다.
#endif // _DEBUG

	// 내가 사용하는 다이렉트 버전값으로 초기화해준다.
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// D3D_FEATURE_LEVEL eLVArr[3] = { D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_0;
	// 만약 여러 버전을 병행선택하고 싶을 때는 위의 코드를 사용하면 된다.
	
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE <= 연산 대상을 GPU로 설정해준 것.
	// SOFTWARE 일 시는 CPU
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

	CreateSwapChain(); // HWND 연동, 디바이스 컨텍스트 세팅이 끝나면 더블버퍼링을 만들어준다.
}

void GameEngineDirectXDevice::CreateSwapChain() // 다이렉트X 기반의 더블버퍼링 시스템을 만들어준다.
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x &&
		0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		// (그럴 리는 없겠지만) 스크린 사이즈가 마이너스 값일때는 폭파...
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize(); // 해상도 사이즈를 가져온다.

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, };

	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy(); // 버퍼의 사이즈를 지정해주고..

	// 모니터에 간섭해서
	ScInfo.BufferDesc.RefreshRate.Denominator = 1.0f;
	// Denominator == 분모 == xx초당
	ScInfo.BufferDesc.RefreshRate.Numerator = 60.0f;
	// Numerator == 분자 == xx번의 주사율을 설정해준다.
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// 스왑체인 시 스크린의 어느 방향부터 그려줄건지...(위, 아래)

	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 화면에 띄우기 위해서는 그런 용도로 만든다는걸 알려줘야 하는데
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	// 렌더링 파이프라인의 "쉐이더" 단계를 적용하냐 적용하지 않냐의 여부

	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1; // 샘플링을 쓰냐 안쓰냐의 여부... 1이면 사용, 0이면 사용안함
	// 샘플링


	ScInfo.OutputWindow = GameEngineWindow::GetInst().GetWindowHWND();

	ScInfo.BufferCount = 2;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

	// 전체화면 모드 가능
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 전체화면 안함.
	ScInfo.Windowed = true;

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
	BackBufferTarget_ = GameEngineRenderTargetManager::GetInst().Create("BackBuffer", "BackBuffer", float4::BLUE);

}


void GameEngineDirectXDevice::RenderStart()
{
	// BackBufferTarget_ <= 여기에 그린 녀석만 나와.
	// 지우고
	BackBufferTarget_->Clear();
	// 세팅하고
	BackBufferTarget_->Setting();
}


void GameEngineDirectXDevice::RenderEnd()
{
	// 화면에 뿌려라
	// BackBufferTarget_;
}