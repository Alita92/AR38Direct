
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

Texture2D Tex : register(t0); // �ְ� ��� �ؽ�ó(���� ���)
Texture2D TexUV : register(t1); // UV �ְ�� �ؽ�ó(�׷��̽�����)
SamplerState Smp : register(s0); // GPU���� �о���̱� ���� ���÷� ����

float4 Curved_PS(VertexOut _in) : SV_Target0
{
    float4 UVMulty = TexUV.Sample(Smp, _in.Texcoord.xy);  // ���� UV �ְ�� �׷��̽������� ���ø��Ѵ�
    float2 CalUv = _in.Texcoord.xy; // UV �ְ��� ���� ���� CalUV �� ����
    
    if (UVMulty.x > 0.5f) // UV x���� 0.5 �̻��̸�(= �߰� ���� ������ �κ��̸�..)
    {CalUv.y += (UVMulty.x - 0.5f) * 0.3f;}
    else if (UVMulty.x < 0.5f)
    {CalUv.y -= (0.5f - UVMulty.x) * 0.3f;}
    // ���������� �ְ��� ����� �κ� - ���ͳ� ����...
        
    float4 Color = Tex.Sample(Smp, CalUv);
    // �ְ� ��� �ؽ�ó��, �ְ��Ų Texcoord.xy �� �ٽñ� ���ø�
    
    if (Color.a >= 1.0f)
    {Color.a = 1.0f;}
    
    if (Color.a <= 0.0f)
    {Color.a = 0.0f;}
    
    return Color;
}


