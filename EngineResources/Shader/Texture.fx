#include "CbufferHeader.fx"

struct VertexIn
{
    // 버텍스 셰이더에 입력으로 들어가는 시멘틱 두 개, 구조체로 묶었다.
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    // 버텍스 셰이더의 출력으로 나오는 시멘틱 두 개.
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};


cbuffer TextureCutData : register(b1)
{
    // 0.0f 0.0f 
    float2 TextureCutDataPos;
    // 1 / 8 1 / 8
    float2 TextureCutDataSize;
};


// '텍스처' 에 사용될 버텍스 셰이더
VertexOut Texture_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

  
    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);
    // 받아들인 POSITION 에 월드X뷰X투영 행렬을 입히는 작업
    
    // 0 0 
    // 1, 0
    // 1, 1
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.x = (_in.Texcoord.x * TextureCutDataSize.x) + TextureCutDataPos.x;
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.y = (_in.Texcoord.y * TextureCutDataSize.y) + TextureCutDataPos.y;

    return Out;
}

cbuffer ResultColor : register(b0)
{
    float4 vColor;
};


Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
// 리소스 선언에 register() 는, GPU가 엑세스할 수 있는 통로이다.
// 최대 15개가 만들어질 수 있으며, 각 버퍼는 총 4096개의 상수 변수를 보유할 수 있다.
// b : 상수 버퍼
// t : 텍스처
// s : 샘플러
// 뒤에 붙는 숫자는 순번

// '텍스처' 에 사용될 픽셀 셰이더
float4 Texture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy) * vColor;

    if (0.0f == Color.a)
    {
        clip(-1);
    }
        

    return Color;
}


