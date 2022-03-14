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

cbuffer TextureCutData : register(b1)
{
    // 0.0f 0.0f
    float2 TextureCutDataPos; 
    // 1 / 8 1 / 8
    float2 TextureCutDataSize;
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

       // 0 0 
    // 1, 0
    // 1, 1
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.x = (_in.Texcoord.x * TextureCutDataSize.x) + TextureCutDataPos.x;
    //                   1                 0.125             +      0.125 * _x
    Out.Texcoord.y = (_in.Texcoord.y * TextureCutDataSize.y) + TextureCutDataPos.y;

    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 Texture_PS(VertexOut _in) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _in.Texcoord.xy); 
    return Color;
}


