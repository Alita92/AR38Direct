
struct VertexIn
{
    float4 Position : POSITION;
    float4 Texcoord : TEXTURECOORD;
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


VertexOut Curved_VS(VertexIn _in)
{
    VertexOut Out;
    Out.Position = _in.Position;
    Out.Texcoord = _in.Texcoord;
    return Out;
}

Texture2D Tex : register(t0);
Texture2D TexUV : register(t1);
SamplerState Smp : register(s0);

float4 Curved_PS(VertexOut _in) : SV_Target0
{
    float4 UVMulty = TexUV.Sample(Smp, _in.Texcoord.xy);
    
    // 0      2
    // -1      1
    // -0.5   1.5f
    // -1.0f   1.0f
    
    float2 CalUv = _in.Texcoord.xy;
    CalUv.x *= 2.0f;
    CalUv.x -= 1.0f;
    CalUv.x *= UVMulty.x;
    CalUv.x += 1.0f;
    CalUv.x /= 2.0f;
    
    CalUv.y *= 2.0f;
    CalUv.y -= 1.0f;
    CalUv.y *= UVMulty.x;
    CalUv.y += 1.0f;
    CalUv.y /= 2.0f;

    
    
    float4 Color = Tex.Sample(Smp, CalUv);
    
    if (Color.a >= 1.0f)
    {
        Color.a = 1.0f;
    }
    
    if (Color.a <= 0.0f)
    {
        Color.a = 0.0f;
    }
    
    
    return Color;
}


