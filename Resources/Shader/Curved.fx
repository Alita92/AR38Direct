
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

Texture2D Tex : register(t0); // 왜곡 대상 텍스처(게임 배경)
Texture2D TexUV : register(t1); // UV 왜곡용 텍스처(그레이스케일)
SamplerState Smp : register(s0); // GPU에서 읽어들이기 위한 샘플러 버퍼

float4 Curved_PS(VertexOut _in) : SV_Target0
{
    float4 UVMulty = TexUV.Sample(Smp, _in.Texcoord.xy);  // 먼저 UV 왜곡용 그레이스케일을 샘플링한다
    float2 CalUv = _in.Texcoord.xy; // UV 왜곡을 위한 버퍼 CalUV 에 장입
    
    if (UVMulty.x > 0.5f) // UV x값이 0.5 이상이면(= 중간 기준 오른쪽 부분이면..)
    {CalUv.y += (UVMulty.x - 0.5f) * 0.3f;}
    else if (UVMulty.x < 0.5f)
    {CalUv.y -= (0.5f - UVMulty.x) * 0.3f;}
    // 실질적으로 왜곡이 적용된 부분 - 인터넷 복붙...
        
    float4 Color = Tex.Sample(Smp, CalUv);
    // 왜곡 대상 텍스처에, 왜곡시킨 Texcoord.xy 를 다시금 샘플링
    
    if (Color.a >= 1.0f)
    {Color.a = 1.0f;}
    
    if (Color.a <= 0.0f)
    {Color.a = 0.0f;}
    
    return Color;
}


