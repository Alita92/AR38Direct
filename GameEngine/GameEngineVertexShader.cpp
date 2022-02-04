#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader() // default constructer 디폴트 생성자
	: VersionHigh_(5)
	, VersionLow_(0)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer 디폴트 소멸자
{
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
		LayOut_ = nullptr;
	}

	if (nullptr != CodeBlob_)
	{
		CodeBlob_->Release();
		CodeBlob_ = nullptr;
	}

}

bool GameEngineVertexShader::Create(
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion();

	return Compile();
}

void GameEngineVertexShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineVertexShader::CreateVersion()
{
	Version_ = "";
	Version_ += "vs_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineVertexShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineVertexShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

bool GameEngineVertexShader::Compile()
{
	// 스트링 받아서 컴파일에 넣어 주면 셰이더가 완성된다.
	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 00000000 00000000 00000000 00000101

	// 행렬이 전치가 되서 들어가는것을 막아준다.
	// 전치가 기본이고 전치된걸 다시 
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// 결과물의 바이트코드

	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),
		Version_.c_str(),
		0,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	VertexShader_;

	// 버텍스쉐이더를 만들어준다... 실패 시 오류 띄우게 하고
	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(), CodeBlob_->GetBufferSize(), nullptr, &VertexShader_))
	{
		GameEngineDebug::MsgBoxError("버텍스 버퍼 생성에 실패했습니다.");
		return false;
	}

	// 성공 시 레이아웃 체크 실행
	LayOutCheck();

	// true 리턴
	return true;
}

void GameEngineVertexShader::AddInputLayOut(
	const char* _SemanticName,
	unsigned int _Index,
	unsigned int _AlignedByteOffset,
	DXGI_FORMAT _Format,
	unsigned int _InputSlot,
	unsigned int _InstanceDataStepRate,
	D3D11_INPUT_CLASSIFICATION _inputClass
)
{
	SemanticName_.push_back(_SemanticName); // 정해 준 시멘틱 이름을 벡터구조에 넣어 주고...

	D3D11_INPUT_ELEMENT_DESC LayOutDesc = { 0, };

	// https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

	LayOutDesc.SemanticName = _SemanticName;
	// 시멘틱 이름 : 요소의 목적을 나타내는 이름표. 예로 위치를 표현할 시 Position 으로 하면 된다.
	//                          0
	LayOutDesc.SemanticIndex = _Index;
	// 시멘틱 인덱스 : 시멘틱 이름을 보충한다; 버텍스는 동일한 속성을 여러 개 가질 수 있기 때문에, 그 동일한 속성 내의 순번을 결정짓는다.
	// Position 1, Position 2 처럼...이 경우 시멘틱 이름은 둘다 Position 이고, 서로 다른 인덱스는 1과 2를 가지는 것!
	//                 DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayOutDesc.Format = _Format;
	// 포맷 : 사용하는 데이터타입을 정의한다. 예로 float4 를 사용하면 32비트(=4바이트) 4개를 사용한다고 알려주는 것...

	LayOutDesc.InputSlot = _InputSlot;
	//                                  신경쓰지마
	LayOutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	//		보류
	//                               16
	LayOutDesc.AlignedByteOffset = LayOutOffset_;
	// 얼라인드 바이트 오프셋 :  GPU에게 이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.


	// 
	LayOutOffset_ += _AlignedByteOffset;

	InputLayoutDesc_.push_back(LayOutDesc);

	//struct GameEngineVertex
	//{
	//public:
	//	// 포지션
	//	// 텍스처 비율
	//	float4 Postion1; POSTION 1 0
	//	float4 Postion0; POSTION 0 16
	//  float4 Postion2; POSTION 2 32 
	//	float4 Color; COLOR 0 48
	//}


	// 
}

void GameEngineVertexShader::CreateLayOut()
{
	if (
		S_OK != GameEngineDevice::GetInst().GetDevice()->CreateInputLayout
		(
			&InputLayoutDesc_[0],
			static_cast<unsigned int>(InputLayoutDesc_.size()),
			CodeBlob_->GetBufferPointer(),
			CodeBlob_->GetBufferSize(),
			&LayOut_
		)
		)
	{
		GameEngineDebug::MsgBoxError("인풋레이아웃 생성에 실패했습니다.");
		return;
	}


}

void GameEngineVertexShader::LayOutCheck()
{
	LayOutClear();

	if (nullptr == CodeBlob_) // 코드블롭이 없으면...
	{
		// 함수를 실행하지 않는다. 
		return;
	}


	ID3D11ShaderReflection* CompilInfo;
	// 셰이더 리플렉션
	// 내가 쉐이더에서 사용한 변수 함수들 인자들 그 이외의 상수버퍼등등등등의 모든
	// 정보를 알고 있는 녀석 (사용내역?)
	// "현재 쉐이더에서 행렬을 x개 사용 중" 같은 정보를 담고 있다.

	// D3DReflect() : 인자 리플렉션의 인터페이스에 대한 포인터를 가져온다.
	// 못 가져오면 뭔가 잘못된 것이니 터뜨려주자.
	if (S_OK != D3DReflect
	(
		CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(&CompilInfo)
	)
		)
	{
		// 뭔가 코드가 이상함.
		GameEngineDebug::MsgBoxError("쉐이더 컴파일 정보를 얻어오지 못했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info; // 셰이더 정보

	CompilInfo->GetDesc(&Info); // 알아서 정보를 채워 주는 함수...

	std::string Name = "";
	int PrevIndex = 0;

	// for 문을 돌며 메모리를 하나하나 타면서 구조체 내부 요소를 분석후 순번을 매긴다
	for (unsigned int i = 0; i < Info.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC Input = { 0, };

		CompilInfo->GetInputParameterDesc(i, &Input);

		DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

		// 타입이 정수인지 실수인지 부호가 있는지 없는지에 대한 ENUM
		// UINT32, FLOAT32 이런 식으로...
		D3D_REGISTER_COMPONENT_TYPE Reg = Input.ComponentType;

		// float4
		// 1 1 1 1 = 16

		// float3
		// 0 1 1 1 = 7

		unsigned int ParameterSize = 0;

		// 마스크
		// 조금 햇갈릴것
		// 들어오는 정보의 메모리 크기를 계산해 스위치로 넘겨
		// ParameterSize 를 바꿔 준다.

		// 예) float4 는 1 1 1 1 == 이진수합 15 == Case 15
		// float3 은 0 1 1 1 == 이진수합 7 == Case 7
		// 이런 식으로..

		// 지금, 버텍스 셰이더 인자로 float4 를 넣어줬으니
		// Reg 는 Float32 가 들어갈 것이고,
		// 마스크는 15로 들어갈 것이다!
		// 그 안에서 포맷도 바꿔 준다...
		switch (Input.Mask)
		{
			// 1개짜리
		case 1:
			ParameterSize = 4;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				// float형 정보라는 뜻
				break;
			default:
				break;
			}
			break;
		case 3:
			ParameterSize = 8;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				// float형 정보라는 뜻
				break;
			default:
				break;
			}
			break;
		case 7:
			ParameterSize = 12;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				// float형 정보라는 뜻
				break;
			default:
				break;
			}
			break;
		case 15:
			ParameterSize = 16;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// float형 정보라는 뜻
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		// 현재 선생님의 프레임워크에서는,
		// Position2 -> position1
		// 이런 식으로 인자 인덱스가 순서대로가 아닌 걸 터뜨릴 것이다.
		// 하기 코드가 그 용도이다.
		std::string NextName = Input.SemanticName;

		if (Name == "")
		{
			Name = NextName;
			++PrevIndex;
		}
		else
		{
			if (Name == NextName)
			{
				if (PrevIndex != Input.SemanticIndex)
				{
					GameEngineDebug::MsgBoxError("시맨틱의 인덱스 순서가 잘못되었습니다 오름차순이 아닙니다..");
					return;
				}

				++PrevIndex;
				// 저 순서가 어때야 합니까?
			}
			else
			{
				Name = NextName;
				PrevIndex = 0;
			}
		}

		// 이것도 안된다.
		//Postion0;
		//Postion3;

		if (DXGI_FORMAT::DXGI_FORMAT_UNKNOWN == Format)
		{	// 포맷을 제대로 밝혀내지 못하면... 파괴!
			GameEngineDebug::MsgBoxError("쉐이더 인풋 파라미터 타입이 정상적이지 않습니다.");
		}

		// 여기서, 이제 구해낸 인자를 인풋레이아웃에 추가해준다.
		AddInputLayOut(Input.SemanticName, Input.SemanticIndex, ParameterSize, Format, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	}

	CreateLayOut();
}


void GameEngineVertexShader::LayOutClear()
{
	if (nullptr != LayOut_)
	{
		LayOut_->Release();
	}

	LayOut_ = nullptr;
	InputLayoutDesc_.clear();
	SemanticName_.clear();
	LayOutOffset_ = 0;
}



void GameEngineVertexShader::InputLayOutSetting()
{
	if (nullptr == LayOut_)
	{
		GameEngineDebug::MsgBoxError("쉐이더 인풋 파라미터가 존재하지 않습니다.");
	}

	GameEngineDevice::GetInst().GetContext()->IASetInputLayout(LayOut_);
}

void GameEngineVertexShader::Setting()
{
	GameEngineDevice::GetInst().GetContext()->VSSetShader(VertexShader_, nullptr, 0);
}