#include "CbufferHeader.fx"

//1. ø¿∏Æ¡ˆ≥Øæ¿∑ª¥ı≈∏∞Ÿø° ø¿∏Æ¡ˆ≥Øæ¿¿ª ∑ª¥ı∏µ


//1.
//ø÷∞Ó¿Ã∆Â∆Æ∑ª¥ı≈∏∞Ÿø° ø÷∞Ó¿Ã∆Â∆Æ∏∏¿ª
//∑ª¥ı∏µ
// 
//2. ø¿∏Æ¡ˆ≥Øæ¿≈ÿΩ∫√ƒøÕ
//ø÷∞Ó¿Ã∆Â∆Æ≈ÿΩ∫√ƒ∏¶ ∫Ì∑ªµÂΩ√ƒ—
//√‚∑¬


struct VertexIn
{
    float4 Position : POSITION;
    float4 Distortion : COLOR0;
    float4 Texcoord : TEXTURECOORD;
};

struct VertexOut
{
    float4 Position : SV_POSITION;
    float4 Distortion : COLOR0;
    float4 Texcoord : TEXTURECOORD;
};


cbuffer TextureCutData : register(b1)
{
    // 0.0f 0.0f 
    float2 TextureCutDataPos;
    // 1 / 8 1 / 8
    float2 TextureCutDataSize;
};


VertexOut Distortion_VS(VertexIn _in)
{
    VertexOut Out;

    Out.Position = _in.Position;

  
    Out.Position.w = 1.0f;
    Out.Position = mul(Out.Position, WVP);

    Out.Distortion = _in.Distortion;
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

float4 Distortion_PS(Distortion_VS _in) : COLOR
{
    float4 Out = 0;
    float2 Trans = _In.uv + 0.001f;
    float4 Noise = tex2D(Samp_Texture_Distortion, Trans);

    float2 UV = _In.uv + Noise.xy * 0.05f;


    float4 Orig = tex2D(Samp_Texture_Orig, UV);

 
    Out = Orig;

    return Out;
}


