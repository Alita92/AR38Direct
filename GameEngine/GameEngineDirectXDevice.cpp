#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"

GameEngineDirectXDevice::GameEngineDirectXDevice() // default constructer 디폴트 생성자
	: Device_(nullptr)
	, Context_(nullptr)
	, SwapChain_(nullptr)
{

}

GameEngineDirectXDevice::~GameEngineDirectXDevice() // default destructer 디폴트 소멸자
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
}
