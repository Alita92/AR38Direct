#include "CbufferHeader.fx"

struct VertexIn
{
    float4 Position : POSITION; // 위치 데이터
    float4 Texcoord : TEXTURECOORD; // 컬러 데이터
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Texcoord : TEXTURECOORD;
};


VertexOut Texture_VS(VertexIn _in)
{

    // 이 내부에서
    // VertexIn 구조체에 UV 값이 적용되어 변환되고
    // VertexOut 구조체로 다시 Return 해 줍니다.

    VertexOut Out;

    Out.Position = _in.Position;

    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);

    Out.Texcoord = _in.Texcoord;

    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 Texture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy); 
    return Color;
}


