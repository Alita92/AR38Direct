#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBufferManager.h"
#include "GameEngineResourcesManager.h"

GameEngineShader::GameEngineShader(ShaderType _Type)
	: VersionHigh_(5)
	, VersionLow_(0)
	, Type_(_Type)
{
}

GameEngineShader::~GameEngineShader()
{
}


void GameEngineShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType)
{
	Version_ = "";
	Version_ += _ShaderType + "_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

// 셰이더 리소스의 유무를 확인하고 있다면 등록시킨다
// 상수 버퍼, 샘플러, 텍스처...
void GameEngineShader::ResCheck()
{
	if (nullptr == CodeBlob_)
	{
		return;
	}

	// 내가 쉐이더에서 사용한 변수 함수들 인자들 그 이외의 상수버퍼등등등등의 모든
	// 정보를 알고 있는 녀석
	// 이 사람 쉐이더에서 행렬1개사용함
	ID3D11ShaderReflection* CompilInfo;

	// 셰이더 컴파일 정보 가져오기
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

	D3D11_SHADER_DESC Info;
	CompilInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResInfo;

	for (unsigned int i = 0; i < Info.BoundResources; i++)
	{
		CompilInfo->GetResourceBindingDesc(i, &ResInfo);

		//LPCSTR                      Name;           // Name of the resource
		//D3D_SHADER_INPUT_TYPE       Type;           // Type of resource (e.g. texture, cbuffer, etc.)
		//UINT                        BindPoint;      // Starting bind point
		//UINT                        BindCount;      // Number of contiguous bind points (for arrays)
		//UINT                        uFlags;         // Input binding flags
		//D3D_RESOURCE_RETURN_TYPE    ReturnType;     // Return type (if texture) 
		//D3D_SRV_DIMENSION           Dimension;      // Dimension (if texture) // 3차원 텍스처
		//UINT                        NumSamples;     // Number of samples (0 if not MS texture)



		std::string Name = ResInfo.Name;
		unsigned int BindPoint = ResInfo.BindPoint;
		D3D_SHADER_INPUT_TYPE Type = ResInfo.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER: // 상수 버퍼가 인식될 경우
		{
			ID3D11ShaderReflectionConstantBuffer* Buffer = CompilInfo->GetConstantBufferByName(Name.c_str());

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			Buffer->GetDesc(&BufferDesc);

			GameEngineConstantBuffer* NewBuffer = GameEngineConstantBufferManager::GetInst().CreateAndFind(Name, BufferDesc, Buffer);

			if (BufferDesc.Size != NewBuffer->GetBufferSize())
			{
				GameEngineDebug::MsgBoxError("구조가 다른 상수버퍼가 존재합니다.");
				return;
			}

			ConstanceBuffers_.insert(std::make_pair(ResInfo.BindPoint, NewBuffer));
			break;
		}
		case D3D_SIT_SAMPLER: // 샘플러가 인식될 경우
		{	// 샘플러 설정은 그냥 여기서 한 번에 다 처리해주자... 
			D3D11_SAMPLER_DESC Smp_Decs = {};

			memset(&Smp_Decs, 0, sizeof(D3D11_SAMPLER_DESC));


			// 라이너 : 뭉개라 <= 기본 값이다.
			Smp_Decs.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			// 포인트 : 딱딱 도트처럼 만들어라
			// Smp_Decs.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

			Smp_Decs.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP; // 비율 값에 근거해서 텍스처가 들어감... 들어가는 메쉬가 2.0 이라고 두개씩 찍히지 않음
			Smp_Decs.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP; // WRAP 으로 하면 바둑판식 배열로 들어감
			Smp_Decs.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

			Smp_Decs.MipLODBias = 0.0f;
			Smp_Decs.MaxAnisotropy = 1;
			Smp_Decs.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			Smp_Decs.MinLOD = -FLT_MAX;
			Smp_Decs.MaxLOD = FLT_MAX;
			// Smp_Decs.BorderColor;
			// Smp_Decs.MaxAnisotropy;

			GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().CreateAndFind(Name, Smp_Decs);
			Samplers_.insert(std::make_pair(ResInfo.BindPoint, NewRes));
			break;
		}

		case D3D_SIT_TEXTURE: // 텍스처가 인식될 경우
		{
			Textures_.insert(std::make_pair(ResInfo.BindPoint, Name));
			break;
		}
		default:
			GameEngineDebug::MsgBoxError("처리하지 못하는 타입의 쉐이더 리소스가 발견되었습니다");
			break;
		}
	}
}